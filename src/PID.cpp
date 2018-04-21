#include "PID.h"

using namespace std;
#include <iostream>
#include <math.h>

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
    Kp =  Kp_;
    Ki =  Ki_;
    Kd =  Kd_;
    p_error = d_error = i_error = 0.0;
   dp = {0.1*Kp,0.1*Kd,0.1*Ki};  // start with a 10% variance
    //dp = {1.0,1.0,1.0};    step = 0;
    param_index = 0;
    total_error = 0;
    best_error = std::numeric_limits<double>::max();
    n_settle_steps = 100;
    n_eval_steps =  200;
    twiddle =  false;
    
}

void PID::UpdateError(double cte) {
    // d_error is difference from old cte (p_error) to the new cte
    d_error = (cte - p_error);
    // p_error gets set to the new cte
    p_error = cte;
    // i_error is the sum of ctes to this point
    i_error += cte;
    
  
    
    if (twiddle) {
        if (step == 0) {
            cout << " Kp " << Kp << " Kd " << Kd << " Ki " << Ki << endl;
        }
    
        step++;    // Code for twiddle stuff
        if (step > n_settle_steps) {
            total_error += cte * cte;
        }
   
        if ((step % n_eval_steps) == 0) {
            cout << " Kp " << Kp << " Kd " << Kd << " Ki " << Ki << endl;
            cout << " perror " << p_error << " derror " << d_error << " ierror " << i_error << endl;
            cout << " Kpd " << dp[0] << " Kdd " << dp[1] << " Kid " << dp[2] << endl;
            step = 0;
            total_error = total_error / 100.0;
            double dperror = dp[0] + dp[1] + dp[2];
            if (dperror > .0001) {
                if (state == 0)  {
                    if (param_index == 0) {
                        Kp += dp[0];
                    } else if  (param_index == 1) {
                        Kd += dp[1];
                    } else {
                        Ki += dp[2];
                    }
                    state = 1;
                } else if (state == 1) {
                    if (total_error < best_error)  {
                        best_error =  total_error;
                        dp[param_index] =  1.1 * dp[param_index];
                        state  = 0;
                        param_index =  (param_index + 1) % 3;
                    } else  {
                        if (param_index == 0) {
                            Kp -= 2.0 * dp[0];
                        } else if  (param_index == 1) {
                            Kd -= 2.0 * dp[1];
                        } else {
                            Ki -= 2.0 * dp[2];
                        }
                        state = 2;
                    }
                } else if (state == 2) {
                    if (total_error < best_error)  {
                        best_error =  total_error;
                        dp[param_index] =  1.1 * dp[param_index];
                    } else {
                        if (param_index == 0) {
                            Kp += dp[0];
                        } else if  (param_index == 1) {
                            Kd += dp[1];
                        } else {
                            Ki += dp[2];
                        }
                        dp[param_index] =  0.9 * dp[param_index];
                    }
                    state  = 0;
                    param_index =  (param_index + 1) % 3;
                }
            }// if dperror  > 0.0001
        } // if step % n_eval_steps
    }
} // end Of Update Method


double PID::TotalError() {
    cout << " perror " << p_error << " derror " << d_error << " ierror " << i_error << endl;
    return -Kp * p_error - Kd * d_error - Ki * i_error;
}

