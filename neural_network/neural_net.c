#include "neural_net.h"
#include "unistd.h"

neuralnet* create_neur(double lr, int in, int hid, int out)
{
    neuralnet* neu = malloc(sizeof(neuralnet));
    neu->lr = lr;
    neu->input = in;
    neu->output = out;

    matrix* hidd_wgt = create_mat(out, hid);
    matrix* out_wgt = create_mat(hid,in);

    fill_rand_m(hidd_wgt);
    fill_rand_m(out_wgt);

    neu->hidden_w = hidd_wgt;
    neu->output_w = out_wgt;

    return neu;
}

void train_net(neuralnet* neu, matrix* in, matrix* out)
{
    //Proccess Forward propagation
    matrix* hidd_ins = dot_m(neu->hidden_w, in);
    matrix* hidd_out = sig_m(hidd_ins);

    matrix* out_ins = dot_m(neu->output_w, hidd_out);
    matrix* out_out = sig_m(out_ins);


    //Compute error rate
    matrix* out_err = sub_m(out, out_out);

    matrix* tmp_err = trans_m(neu->output_w);
    matrix* hid_err = dot_m(tmp_err,out_err);
    free_m(tmp_err);

    //Proccess Backprogation
    matrix* DSigmo_m = Dsig_m(out_out);
    matrix* mul_m = mult_m(out_err, DSigmo_m);
    matrix* tra_m = trans_m(hidd_out);
    matrix* dotted_m = dot_m(mul_m, tra_m);
    matrix* sca_m = mult_scale_m(dotted_m, neu->lr);
    matrix* added_m = add_m(neu->output_w, sca_m);
    
    free(neu->output_w);
    neu->output_w = added_m;

    //Freeing memory
    free_m(sca_m);
    free_m(dotted_m);
    free_m(tra_m);
    free_m(mul_m);
    free_m(DSigmo_m);

    matrix* sigmo_m = sig_m(hidd_out);
    matrix* m_m = mult_m(hid_err,sigmo_m);
    matrix* t_m = trans_m(in);
    matrix* d_m = dot_m(t_m, m_m);
    matrix* lr_m = mult_scale_m(d_m, neu->lr);
    matrix* a_m = add_m(neu->hidden_w, lr_m);
    neu->hidden_w = a_m;

    free_m(a_m);
    free_m(lr_m);
    free_m(d_m);
    free_m(t_m);
    free_m(m_m);
    free_m(sigmo_m);
    free_m(out_err);
    free_m(hid_err);
    free_m(out_out);
    free_m(out_ins);
    free_m(hidd_ins);
    free_m(hidd_out);
}

void train_xor()
{
    neuralnet* res = create_neur(0.1f,2,2,1);

    double inp[4][2] = {{0.0f,0.0f},{0.0f,1.0f},{1.0f,0.0f},{1.0f,1.0f}};
    double outp[4][1] ={ {0.0f},{1.0f},{1.0f},{0.0f}};

    matrix* out = create_mat(1,1);
    matrix* in = create_mat(2,1);

    for(int i = 0; i < 1000; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 2; k++)
            {
                in->inputs[k][0] = inp[j][k]; 
            }
            out->inputs[0][0] = outp[j][0];
            train_net(res,in,out);
        }
    }
    printf("outputs : %f \n",out->inputs[3][0]);

}
