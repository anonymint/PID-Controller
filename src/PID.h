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
  double sumCTESqrError;
  double numCTECount;

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
};

#endif /* PID_H */
