#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  std::cout << "starting the value "<<Kp << " " << Ki << " "<< Kd << std::endl;
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
  //reset error   
  sumCTESqrError = 0.0;
  numCTECount = 0.0;
}

void PID::UpdateError(double cte) {
    d_error = cte - p_error;
    p_error = cte;
    i_error += cte;    

    // update error tracking
    if (enabledTwiddle) {
        sumCTESqrError += pow(cte, 2);
        numCTECount += 1;
    }    
}

double PID::TotalError() {
    return -Kp*p_error - Kd*d_error - Ki*i_error; 
}

double PID::GetError() {
    return sqrt(sumCTESqrError / numCTECount);
}

void PID::ResetError() {
    sumCTESqrError = 0.0;
    numCTECount = 0.0;
}

void PID::Twiddle() {    
    if (!initialTwiddle) {
        counterJ = 0;        
        bestErr = GetError();   
        bestKp = Kp;
        bestKi = Ki;
        bestKd = Kd;     
        startErr = bestErr;
        initialTwiddle = true;
        
        //initial first twiddle
        caseCon = 1;
        K[counterJ] += dK[counterJ];
        Init(K[0], K[1], K[2]);        
    } else {
        if (counterJ/3 < iterationCount) {
            std::cout << "I:" << iterationCount << "J:" << counterJ << "PID" << Kp << " " << Ki << " " << Kd << " " << std::endl;
            int j = counterJ % 3;
            double errJ = GetError();
            // check case if 1 just check best and initial 
            // case 2 check best and increase counter
            if (caseCon == 1) {
                if (errJ < bestErr) {
                    bestErr = errJ;
                    bestKp = Kp;
                    bestKi = Ki;
                    bestKd = Kd;                         
                    dK[j] *= 1.1;
                    // initial                    
                    counterJ += 1;
                    K[counterJ%3] += dK[counterJ%3];
                    Init(K[0], K[1], K[2]);
                } else {
                    caseCon = 2;
                    // initial
                    K[j] -= 2*dK[j];
                    Init(K[0], K[1], K[2]);
                }
            } else if (caseCon == 2) {
                if (errJ < bestErr) {
                    bestErr = errJ;
                    bestKp = Kp;
                    bestKi = Ki;
                    bestKd = Kd;     
                    dK[j] *= 1.1;
                    // initial
                    counterJ += 1;
                    K[counterJ%3] += dK[counterJ%3];
                    Init(K[0], K[1], K[2]);
                    caseCon = 1;
                } else {
                    K[j] += dK[j];
                    dK[j] *= 0.9;
                    // initial
                    counterJ += 1;
                    K[counterJ%3] += dK[counterJ%3];
                    Init(K[0], K[1], K[2]);
                    caseCon = 1;
                }    
            }       
        } else {
            std::cout << "Start Err:" << startErr << " End Err:" << GetError() << std::endl;
            std::cout << "Best PID:" << bestKp << " " << bestKi << " " << bestKd << std::endl;
            std::cout << "Best dK:" << dK[0] << " " << dK[1] << " " << dK[2] << std::endl;
            exit(1);
        }
        
    }    
}