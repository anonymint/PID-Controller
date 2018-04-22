#ifndef PID_H
#define PID_H

#include <iostream>
#include <random>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  /*
  * Helper variables
  */
  bool enabledTwiddle = false;
  int counter;
  int counterReset;
  int iterationCount;
  std::vector<double> K;
  std::vector<double> dK;
  double sumCTESqrError;
  double numCTECount;
  bool initialTwiddle;
  double startErr;
  double bestErr;
  double bestKp;
  double bestKi;
  double bestKd;
  int counterJ;
  int caseCon;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /*
  * get Error 
  */
  double GetError();

  /*
  * reset Error
  */
  void ResetError();

  /*
  * Twiddle
  */
  void Twiddle();
};

#endif /* PID_H */
