/*
 * part4_open_loop_heli.c
 *
 * Code generation for model "part4_open_loop_heli".
 *
 * Model version              : 1.225
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Thu Mar 15 12:21:34 2018
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "part4_open_loop_heli.h"
#include "part4_open_loop_heli_private.h"
#include "part4_open_loop_heli_dt.h"

/* Block signals (auto storage) */
B_part4_open_loop_heli_T part4_open_loop_heli_B;

/* Continuous states */
X_part4_open_loop_heli_T part4_open_loop_heli_X;

/* Block states (auto storage) */
DW_part4_open_loop_heli_T part4_open_loop_heli_DW;

/* Real-time model */
RT_MODEL_part4_open_loop_heli_T part4_open_loop_heli_M_;
RT_MODEL_part4_open_loop_heli_T *const part4_open_loop_heli_M =
  &part4_open_loop_heli_M_;

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  part4_open_loop_heli_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void part4_open_loop_heli_output(void)
{
  /* local block i/o variables */
  real_T rtb_FromWorkspace2[2];
  real_T rtb_Backgain;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T *lastU;
  real_T rtb_Derivative;
  if (rtmIsMajorTimeStep(part4_open_loop_heli_M)) {
    /* set solver stop time */
    if (!(part4_open_loop_heli_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&part4_open_loop_heli_M->solverInfo,
                            ((part4_open_loop_heli_M->Timing.clockTickH0 + 1) *
        part4_open_loop_heli_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&part4_open_loop_heli_M->solverInfo,
                            ((part4_open_loop_heli_M->Timing.clockTick0 + 1) *
        part4_open_loop_heli_M->Timing.stepSize0 +
        part4_open_loop_heli_M->Timing.clockTickH0 *
        part4_open_loop_heli_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(part4_open_loop_heli_M)) {
    part4_open_loop_heli_M->Timing.t[0] = rtsiGetT
      (&part4_open_loop_heli_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(part4_open_loop_heli_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: part4_open_loop_heli/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (part4_open_loop_heli_DW.HILReadEncoderTimebase_Task, 1,
         &part4_open_loop_heli_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          part4_open_loop_heli_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          part4_open_loop_heli_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          part4_open_loop_heli_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Travel: Count to rad' */
    part4_open_loop_heli_B.TravelCounttorad =
      part4_open_loop_heli_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;

    /* Gain: '<S11>/Gain' */
    part4_open_loop_heli_B.Gain = part4_open_loop_heli_P.Gain_Gain *
      part4_open_loop_heli_B.TravelCounttorad;

    /* Sum: '<Root>/Sum3' incorporates:
     *  Constant: '<Root>/Constant'
     */
    part4_open_loop_heli_B.Sum3 = part4_open_loop_heli_P.x1_0 *
      57.295779513082323 + part4_open_loop_heli_B.Gain;
  }

  /* TransferFcn: '<S4>/Travel: Transfer Fcn' */
  rtb_Backgain = 0.0;
  rtb_Backgain += part4_open_loop_heli_P.TravelTransferFcn_C *
    part4_open_loop_heli_X.TravelTransferFcn_CSTATE;
  rtb_Backgain += part4_open_loop_heli_P.TravelTransferFcn_D *
    part4_open_loop_heli_B.TravelCounttorad;

  /* Gain: '<S12>/Gain' */
  part4_open_loop_heli_B.Gain_d = part4_open_loop_heli_P.Gain_Gain_l *
    rtb_Backgain;
  if (rtmIsMajorTimeStep(part4_open_loop_heli_M)) {
    /* Gain: '<S4>/Pitch: Count to rad' */
    part4_open_loop_heli_B.PitchCounttorad =
      part4_open_loop_heli_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S8>/Gain' */
    part4_open_loop_heli_B.Gain_i = part4_open_loop_heli_P.Gain_Gain_a *
      part4_open_loop_heli_B.PitchCounttorad;
  }

  /* TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  rtb_Backgain = 0.0;
  rtb_Backgain += part4_open_loop_heli_P.PitchTransferFcn_C *
    part4_open_loop_heli_X.PitchTransferFcn_CSTATE;
  rtb_Backgain += part4_open_loop_heli_P.PitchTransferFcn_D *
    part4_open_loop_heli_B.PitchCounttorad;

  /* Gain: '<S9>/Gain' */
  part4_open_loop_heli_B.Gain_b = part4_open_loop_heli_P.Gain_Gain_ae *
    rtb_Backgain;
  if (rtmIsMajorTimeStep(part4_open_loop_heli_M)) {
    /* Gain: '<S4>/Elevation: Count to rad' */
    part4_open_loop_heli_B.ElevationCounttorad =
      part4_open_loop_heli_P.ElevationCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o3;

    /* Gain: '<S6>/Gain' */
    part4_open_loop_heli_B.Gain_e = part4_open_loop_heli_P.Gain_Gain_lv *
      part4_open_loop_heli_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    part4_open_loop_heli_B.Sum = part4_open_loop_heli_B.Gain_e +
      part4_open_loop_heli_P.elavation_offsetdeg_Value;
  }

  /* TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  rtb_Backgain = 0.0;
  rtb_Backgain += part4_open_loop_heli_P.ElevationTransferFcn_C *
    part4_open_loop_heli_X.ElevationTransferFcn_CSTATE;
  rtb_Backgain += part4_open_loop_heli_P.ElevationTransferFcn_D *
    part4_open_loop_heli_B.ElevationCounttorad;

  /* Gain: '<S7>/Gain' */
  part4_open_loop_heli_B.Gain_dg = part4_open_loop_heli_P.Gain_Gain_n *
    rtb_Backgain;

  /* Gain: '<S2>/Gain1' */
  part4_open_loop_heli_B.Gain1[0] = part4_open_loop_heli_P.Gain1_Gain *
    part4_open_loop_heli_B.Sum3;
  part4_open_loop_heli_B.Gain1[1] = part4_open_loop_heli_P.Gain1_Gain *
    part4_open_loop_heli_B.Gain_d;
  part4_open_loop_heli_B.Gain1[2] = part4_open_loop_heli_P.Gain1_Gain *
    part4_open_loop_heli_B.Gain_i;
  part4_open_loop_heli_B.Gain1[3] = part4_open_loop_heli_P.Gain1_Gain *
    part4_open_loop_heli_B.Gain_b;
  part4_open_loop_heli_B.Gain1[4] = part4_open_loop_heli_P.Gain1_Gain *
    part4_open_loop_heli_B.Sum;
  part4_open_loop_heli_B.Gain1[5] = part4_open_loop_heli_P.Gain1_Gain *
    part4_open_loop_heli_B.Gain_dg;
  if (rtmIsMajorTimeStep(part4_open_loop_heli_M)) {
    /* ToFile: '<Root>/To File1' */
    {
      if (!(++part4_open_loop_heli_DW.ToFile1_IWORK.Decimation % 1) &&
          (part4_open_loop_heli_DW.ToFile1_IWORK.Count*7)+1 < 100000000 ) {
        FILE *fp = (FILE *) part4_open_loop_heli_DW.ToFile1_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[7];
          part4_open_loop_heli_DW.ToFile1_IWORK.Decimation = 0;
          u[0] = part4_open_loop_heli_M->Timing.t[1];
          u[1] = part4_open_loop_heli_B.Gain1[0];
          u[2] = part4_open_loop_heli_B.Gain1[1];
          u[3] = part4_open_loop_heli_B.Gain1[2];
          u[4] = part4_open_loop_heli_B.Gain1[3];
          u[5] = part4_open_loop_heli_B.Gain1[4];
          u[6] = part4_open_loop_heli_B.Gain1[5];
          if (fwrite(u, sizeof(real_T), 7, fp) != 7) {
            rtmSetErrorStatus(part4_open_loop_heli_M,
                              "Error writing to MAT-file scope_data_open_loop.mat");
            return;
          }

          if (((++part4_open_loop_heli_DW.ToFile1_IWORK.Count)*7)+1 >= 100000000)
          {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file scope_data_open_loop.mat.\n");
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace2' */
  {
    real_T *pDataValues = (real_T *)
      part4_open_loop_heli_DW.FromWorkspace2_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      part4_open_loop_heli_DW.FromWorkspace2_PWORK.TimePtr;
    int_T currTimeIndex = part4_open_loop_heli_DW.FromWorkspace2_IWORK.PrevIndex;
    real_T t = part4_open_loop_heli_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[80]) {
      currTimeIndex = 79;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    part4_open_loop_heli_DW.FromWorkspace2_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_FromWorkspace2[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 81;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_FromWorkspace2[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 81;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 2; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_FromWorkspace2[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1,
              f2);
            pDataValues += 81;
          }
        }
      }
    }
  }

  if (rtmIsMajorTimeStep(part4_open_loop_heli_M)) {
    /* Constant: '<Root>/Vd_bias' */
    part4_open_loop_heli_B.Vd_bias = part4_open_loop_heli_P.Vd_ff;
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Gain: '<S5>/K_pd'
   *  Gain: '<S5>/K_pp'
   *  Sum: '<S5>/Sum2'
   *  Sum: '<S5>/Sum3'
   */
  part4_open_loop_heli_B.Sum1 = ((rtb_FromWorkspace2[0] -
    part4_open_loop_heli_B.Gain1[2]) * part4_open_loop_heli_P.K_pp -
    part4_open_loop_heli_P.K_pd * part4_open_loop_heli_B.Gain1[3]) +
    part4_open_loop_heli_B.Vd_bias;
  if (rtmIsMajorTimeStep(part4_open_loop_heli_M)) {
  }

  /* Integrator: '<S3>/Integrator'
   *
   * Regarding '<S3>/Integrator':
   *  Limited Integrator
   */
  if (part4_open_loop_heli_X.Integrator_CSTATE >=
      part4_open_loop_heli_P.Integrator_UpperSat ) {
    part4_open_loop_heli_X.Integrator_CSTATE =
      part4_open_loop_heli_P.Integrator_UpperSat;
  } else if (part4_open_loop_heli_X.Integrator_CSTATE <=
             (part4_open_loop_heli_P.Integrator_LowerSat) ) {
    part4_open_loop_heli_X.Integrator_CSTATE =
      (part4_open_loop_heli_P.Integrator_LowerSat);
  }

  rtb_Backgain = part4_open_loop_heli_X.Integrator_CSTATE;

  /* Sum: '<S3>/Sum' */
  rtb_Derivative = rtb_FromWorkspace2[1] - part4_open_loop_heli_B.Gain1[4];
  if (rtmIsMajorTimeStep(part4_open_loop_heli_M)) {
    /* Constant: '<Root>/Vs_bias' */
    part4_open_loop_heli_B.Vs_bias = part4_open_loop_heli_P.Vs_ff;
  }

  /* Sum: '<Root>/Sum2' incorporates:
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Sum: '<S3>/Sum1'
   */
  part4_open_loop_heli_B.Sum2 = ((part4_open_loop_heli_P.K_ep * rtb_Derivative +
    rtb_Backgain) - part4_open_loop_heli_P.K_ed * part4_open_loop_heli_B.Gain1[5])
    + part4_open_loop_heli_B.Vs_bias;
  if (rtmIsMajorTimeStep(part4_open_loop_heli_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Backgain = (part4_open_loop_heli_B.Sum2 - part4_open_loop_heli_B.Sum1) *
    part4_open_loop_heli_P.Backgain_Gain;

  /* Gain: '<S3>/K_ei' */
  part4_open_loop_heli_B.K_ei = part4_open_loop_heli_P.K_ei * rtb_Derivative;
  if (rtmIsMajorTimeStep(part4_open_loop_heli_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  if ((part4_open_loop_heli_DW.TimeStampA >= part4_open_loop_heli_M->Timing.t[0])
      && (part4_open_loop_heli_DW.TimeStampB >= part4_open_loop_heli_M->
          Timing.t[0])) {
    rtb_Derivative = 0.0;
  } else {
    rtb_Derivative = part4_open_loop_heli_DW.TimeStampA;
    lastU = &part4_open_loop_heli_DW.LastUAtTimeA;
    if (part4_open_loop_heli_DW.TimeStampA < part4_open_loop_heli_DW.TimeStampB)
    {
      if (part4_open_loop_heli_DW.TimeStampB < part4_open_loop_heli_M->Timing.t
          [0]) {
        rtb_Derivative = part4_open_loop_heli_DW.TimeStampB;
        lastU = &part4_open_loop_heli_DW.LastUAtTimeB;
      }
    } else {
      if (part4_open_loop_heli_DW.TimeStampA >= part4_open_loop_heli_M->
          Timing.t[0]) {
        rtb_Derivative = part4_open_loop_heli_DW.TimeStampB;
        lastU = &part4_open_loop_heli_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (part4_open_loop_heli_B.PitchCounttorad - *lastU) /
      (part4_open_loop_heli_M->Timing.t[0] - rtb_Derivative);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S10>/Gain' */
  part4_open_loop_heli_B.Gain_l = part4_open_loop_heli_P.Gain_Gain_a1 *
    rtb_Derivative;
  if (rtmIsMajorTimeStep(part4_open_loop_heli_M)) {
  }

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Backgain > part4_open_loop_heli_P.BackmotorSaturation_UpperSat) {
    part4_open_loop_heli_B.BackmotorSaturation =
      part4_open_loop_heli_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Backgain < part4_open_loop_heli_P.BackmotorSaturation_LowerSat)
  {
    part4_open_loop_heli_B.BackmotorSaturation =
      part4_open_loop_heli_P.BackmotorSaturation_LowerSat;
  } else {
    part4_open_loop_heli_B.BackmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(part4_open_loop_heli_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Derivative = (part4_open_loop_heli_B.Sum1 + part4_open_loop_heli_B.Sum2) *
    part4_open_loop_heli_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Derivative > part4_open_loop_heli_P.FrontmotorSaturation_UpperSat) {
    part4_open_loop_heli_B.FrontmotorSaturation =
      part4_open_loop_heli_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Derivative <
             part4_open_loop_heli_P.FrontmotorSaturation_LowerSat) {
    part4_open_loop_heli_B.FrontmotorSaturation =
      part4_open_loop_heli_P.FrontmotorSaturation_LowerSat;
  } else {
    part4_open_loop_heli_B.FrontmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(part4_open_loop_heli_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: part4_open_loop_heli/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      part4_open_loop_heli_DW.HILWriteAnalog_Buffer[0] =
        part4_open_loop_heli_B.FrontmotorSaturation;
      part4_open_loop_heli_DW.HILWriteAnalog_Buffer[1] =
        part4_open_loop_heli_B.BackmotorSaturation;
      result = hil_write_analog(part4_open_loop_heli_DW.HILInitialize_Card,
        part4_open_loop_heli_P.HILWriteAnalog_channels, 2,
        &part4_open_loop_heli_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void part4_open_loop_heli_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (part4_open_loop_heli_DW.TimeStampA == (rtInf)) {
    part4_open_loop_heli_DW.TimeStampA = part4_open_loop_heli_M->Timing.t[0];
    lastU = &part4_open_loop_heli_DW.LastUAtTimeA;
  } else if (part4_open_loop_heli_DW.TimeStampB == (rtInf)) {
    part4_open_loop_heli_DW.TimeStampB = part4_open_loop_heli_M->Timing.t[0];
    lastU = &part4_open_loop_heli_DW.LastUAtTimeB;
  } else if (part4_open_loop_heli_DW.TimeStampA <
             part4_open_loop_heli_DW.TimeStampB) {
    part4_open_loop_heli_DW.TimeStampA = part4_open_loop_heli_M->Timing.t[0];
    lastU = &part4_open_loop_heli_DW.LastUAtTimeA;
  } else {
    part4_open_loop_heli_DW.TimeStampB = part4_open_loop_heli_M->Timing.t[0];
    lastU = &part4_open_loop_heli_DW.LastUAtTimeB;
  }

  *lastU = part4_open_loop_heli_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(part4_open_loop_heli_M)) {
    rt_ertODEUpdateContinuousStates(&part4_open_loop_heli_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++part4_open_loop_heli_M->Timing.clockTick0)) {
    ++part4_open_loop_heli_M->Timing.clockTickH0;
  }

  part4_open_loop_heli_M->Timing.t[0] = rtsiGetSolverStopTime
    (&part4_open_loop_heli_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++part4_open_loop_heli_M->Timing.clockTick1)) {
      ++part4_open_loop_heli_M->Timing.clockTickH1;
    }

    part4_open_loop_heli_M->Timing.t[1] =
      part4_open_loop_heli_M->Timing.clockTick1 *
      part4_open_loop_heli_M->Timing.stepSize1 +
      part4_open_loop_heli_M->Timing.clockTickH1 *
      part4_open_loop_heli_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void part4_open_loop_heli_derivatives(void)
{
  XDot_part4_open_loop_heli_T *_rtXdot;
  _rtXdot = ((XDot_part4_open_loop_heli_T *)
             part4_open_loop_heli_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE +=
    part4_open_loop_heli_P.TravelTransferFcn_A *
    part4_open_loop_heli_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += part4_open_loop_heli_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += part4_open_loop_heli_P.PitchTransferFcn_A *
    part4_open_loop_heli_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += part4_open_loop_heli_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    part4_open_loop_heli_P.ElevationTransferFcn_A *
    part4_open_loop_heli_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    part4_open_loop_heli_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  {
    boolean_T lsat;
    boolean_T usat;
    lsat = ( part4_open_loop_heli_X.Integrator_CSTATE <=
            (part4_open_loop_heli_P.Integrator_LowerSat) );
    usat = ( part4_open_loop_heli_X.Integrator_CSTATE >=
            part4_open_loop_heli_P.Integrator_UpperSat );
    if ((!lsat && !usat) ||
        (lsat && (part4_open_loop_heli_B.K_ei > 0)) ||
        (usat && (part4_open_loop_heli_B.K_ei < 0)) ) {
      ((XDot_part4_open_loop_heli_T *) part4_open_loop_heli_M->ModelData.derivs
        )->Integrator_CSTATE = part4_open_loop_heli_B.K_ei;
    } else {
      /* in saturation */
      ((XDot_part4_open_loop_heli_T *) part4_open_loop_heli_M->ModelData.derivs
        )->Integrator_CSTATE = 0.0;
    }
  }
}

/* Model initialize function */
void part4_open_loop_heli_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: part4_open_loop_heli/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &part4_open_loop_heli_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (part4_open_loop_heli_DW.HILInitialize_Card,
       "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(part4_open_loop_heli_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
      return;
    }

    if ((part4_open_loop_heli_P.HILInitialize_set_analog_input_ && !is_switching)
        || (part4_open_loop_heli_P.HILInitialize_set_analog_inpu_m &&
            is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums =
          &part4_open_loop_heli_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] =
            part4_open_loop_heli_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums =
          &part4_open_loop_heli_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] =
            part4_open_loop_heli_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges
        (part4_open_loop_heli_DW.HILInitialize_Card,
         part4_open_loop_heli_P.HILInitialize_analog_input_chan, 8U,
         &part4_open_loop_heli_DW.HILInitialize_AIMinimums[0],
         &part4_open_loop_heli_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
        return;
      }
    }

    if ((part4_open_loop_heli_P.HILInitialize_set_analog_output && !is_switching)
        || (part4_open_loop_heli_P.HILInitialize_set_analog_outp_b &&
            is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums =
          &part4_open_loop_heli_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] =
            part4_open_loop_heli_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums =
          &part4_open_loop_heli_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] =
            part4_open_loop_heli_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges
        (part4_open_loop_heli_DW.HILInitialize_Card,
         part4_open_loop_heli_P.HILInitialize_analog_output_cha, 8U,
         &part4_open_loop_heli_DW.HILInitialize_AOMinimums[0],
         &part4_open_loop_heli_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
        return;
      }
    }

    if ((part4_open_loop_heli_P.HILInitialize_set_analog_outp_e && !is_switching)
        || (part4_open_loop_heli_P.HILInitialize_set_analog_outp_j &&
            is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &part4_open_loop_heli_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] =
            part4_open_loop_heli_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(part4_open_loop_heli_DW.HILInitialize_Card,
        part4_open_loop_heli_P.HILInitialize_analog_output_cha, 8U,
        &part4_open_loop_heli_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
        return;
      }
    }

    if (part4_open_loop_heli_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &part4_open_loop_heli_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] =
            part4_open_loop_heli_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (part4_open_loop_heli_DW.HILInitialize_Card,
         part4_open_loop_heli_P.HILInitialize_analog_output_cha, 8U,
         &part4_open_loop_heli_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
        return;
      }
    }

    if ((part4_open_loop_heli_P.HILInitialize_set_encoder_param && !is_switching)
        || (part4_open_loop_heli_P.HILInitialize_set_encoder_par_m &&
            is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &part4_open_loop_heli_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] =
            part4_open_loop_heli_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (part4_open_loop_heli_DW.HILInitialize_Card,
         part4_open_loop_heli_P.HILInitialize_encoder_channels, 8U,
         (t_encoder_quadrature_mode *)
         &part4_open_loop_heli_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
        return;
      }
    }

    if ((part4_open_loop_heli_P.HILInitialize_set_encoder_count && !is_switching)
        || (part4_open_loop_heli_P.HILInitialize_set_encoder_cou_k &&
            is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &part4_open_loop_heli_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] =
            part4_open_loop_heli_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(part4_open_loop_heli_DW.HILInitialize_Card,
        part4_open_loop_heli_P.HILInitialize_encoder_channels, 8U,
        &part4_open_loop_heli_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
        return;
      }
    }

    if ((part4_open_loop_heli_P.HILInitialize_set_pwm_params_at && !is_switching)
        || (part4_open_loop_heli_P.HILInitialize_set_pwm_params__f &&
            is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &part4_open_loop_heli_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = part4_open_loop_heli_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(part4_open_loop_heli_DW.HILInitialize_Card,
        part4_open_loop_heli_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &part4_open_loop_heli_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          part4_open_loop_heli_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues =
          &part4_open_loop_heli_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            part4_open_loop_heli_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = p_HILInitialize_pwm_channels[i1];
            part4_open_loop_heli_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = part4_open_loop_heli_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            part4_open_loop_heli_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = p_HILInitialize_pwm_channels[i1];
            part4_open_loop_heli_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              part4_open_loop_heli_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency
          (part4_open_loop_heli_DW.HILInitialize_Card,
           &part4_open_loop_heli_DW.HILInitialize_POSortedChans[0],
           num_duty_cycle_modes,
           &part4_open_loop_heli_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle
          (part4_open_loop_heli_DW.HILInitialize_Card,
           &part4_open_loop_heli_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
           num_frequency_modes,
           &part4_open_loop_heli_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &part4_open_loop_heli_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            part4_open_loop_heli_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &part4_open_loop_heli_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] =
            part4_open_loop_heli_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &part4_open_loop_heli_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] =
            part4_open_loop_heli_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration
        (part4_open_loop_heli_DW.HILInitialize_Card,
         part4_open_loop_heli_P.HILInitialize_pwm_channels, 8U,
         (t_pwm_configuration *)
         &part4_open_loop_heli_DW.HILInitialize_POModeValues[0],
         (t_pwm_alignment *)
         &part4_open_loop_heli_DW.HILInitialize_POAlignValues[0],
         (t_pwm_polarity *)
         &part4_open_loop_heli_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &part4_open_loop_heli_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] =
            part4_open_loop_heli_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &part4_open_loop_heli_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] =
            part4_open_loop_heli_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(part4_open_loop_heli_DW.HILInitialize_Card,
        part4_open_loop_heli_P.HILInitialize_pwm_channels, 8U,
        &part4_open_loop_heli_DW.HILInitialize_POSortedFreqs[0],
        &part4_open_loop_heli_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
        return;
      }
    }

    if ((part4_open_loop_heli_P.HILInitialize_set_pwm_outputs_a && !is_switching)
        || (part4_open_loop_heli_P.HILInitialize_set_pwm_outputs_g &&
            is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &part4_open_loop_heli_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] =
            part4_open_loop_heli_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(part4_open_loop_heli_DW.HILInitialize_Card,
        part4_open_loop_heli_P.HILInitialize_pwm_channels, 8U,
        &part4_open_loop_heli_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
        return;
      }
    }

    if (part4_open_loop_heli_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &part4_open_loop_heli_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] =
            part4_open_loop_heli_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (part4_open_loop_heli_DW.HILInitialize_Card,
         part4_open_loop_heli_P.HILInitialize_pwm_channels, 8U,
         &part4_open_loop_heli_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: part4_open_loop_heli/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (part4_open_loop_heli_DW.HILInitialize_Card,
       part4_open_loop_heli_P.HILReadEncoderTimebase_samples_,
       part4_open_loop_heli_P.HILReadEncoderTimebase_channels, 3,
       &part4_open_loop_heli_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/To File1' */
  {
    char fileName[509] = "scope_data_open_loop.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(part4_open_loop_heli_M,
                        "Error creating .mat file scope_data_open_loop.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,7,0,"scope_data_open_loop")) {
      rtmSetErrorStatus(part4_open_loop_heli_M,
                        "Error writing mat file header to file scope_data_open_loop.mat");
      return;
    }

    part4_open_loop_heli_DW.ToFile1_IWORK.Count = 0;
    part4_open_loop_heli_DW.ToFile1_IWORK.Decimation = -1;
    part4_open_loop_heli_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace2' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.36413013597466493, 0.11143169919519186,
      -0.10676534053719404, -0.27223023336076491, -0.39175335565669384,
      -0.47193519981365084, -0.51906238259777238, -0.52359877559829882,
      -0.52359877559829882, -0.51834216577386527, -0.48689267551221754,
      -0.44654865508231323, -0.40052012119879282, -0.35151023484777116,
      -0.30175404176773973, -0.25305653140306572, -0.20684587796485043,
      -0.16421796773269298, -0.12597743196719047, -0.092683552593213023,
      -0.064672529954879016, -0.042081973631616393, -0.024847237414548629,
      -0.012692942101379194, -0.0050967029292585085, -0.0012427120758102589,
      -1.0746709345544791E-6, -6.3860302127655029E-7, -6.155270460735802E-8,
      -1.269112573918634E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.28552341141262727, 0.30300460262737078, 0.31965246833090577,
      0.33487424635390245, 0.34792152581924529, 0.35786235601108607,
      0.36354270804458411, 0.36354284310722706, 0.35612338458919973,
      0.33916576056393333, 0.31009409215317185, 0.26579465921410417,
      0.20251031815426554, 0.11572135250678048, 1.163130731368084E-6,
      7.3196002839469723E-7, 1.1308010981356525E-6, 1.1592699438164758E-6,
      9.8577824788235541E-7, 1.8134997727418786E-6, 1.2472658448479038E-6,
      1.142819918761469E-6, 1.6148166595108851E-6, 8.7199965364582682E-7,
      6.3160812611100754E-7, 7.7933890605234091E-7, 1.5381979307414717E-6,
      8.6302567870237138E-7, 1.0386255528050915E-6, 6.0838749057621143E-7,
      1.2118937381819767E-6, 1.0487300290183539E-6, 9.21536433102461E-7,
      9.8413194199736283E-7, 3.3352809075022889E-7, 3.4907823671332054E-7,
      -5.2984446921958265E-7, -8.1883915727970749E-7, 6.0720891508181833E-7,
      -1.269112573918634E-7, -1.269112573918634E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    part4_open_loop_heli_DW.FromWorkspace2_PWORK.TimePtr = (void *) pTimeValues0;
    part4_open_loop_heli_DW.FromWorkspace2_PWORK.DataPtr = (void *) pDataValues0;
    part4_open_loop_heli_DW.FromWorkspace2_IWORK.PrevIndex = 0;
  }

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  part4_open_loop_heli_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  part4_open_loop_heli_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  part4_open_loop_heli_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  part4_open_loop_heli_X.Integrator_CSTATE =
    part4_open_loop_heli_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  part4_open_loop_heli_DW.TimeStampA = (rtInf);
  part4_open_loop_heli_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void part4_open_loop_heli_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: part4_open_loop_heli/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(part4_open_loop_heli_DW.HILInitialize_Card);
    hil_monitor_stop_all(part4_open_loop_heli_DW.HILInitialize_Card);
    is_switching = false;
    if ((part4_open_loop_heli_P.HILInitialize_set_analog_out_ex && !is_switching)
        || (part4_open_loop_heli_P.HILInitialize_set_analog_outp_c &&
            is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &part4_open_loop_heli_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] =
            part4_open_loop_heli_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((part4_open_loop_heli_P.HILInitialize_set_pwm_output_ap && !is_switching)
        || (part4_open_loop_heli_P.HILInitialize_set_pwm_outputs_p &&
            is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &part4_open_loop_heli_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] =
            part4_open_loop_heli_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(part4_open_loop_heli_DW.HILInitialize_Card
                         ,
                         part4_open_loop_heli_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , part4_open_loop_heli_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &part4_open_loop_heli_DW.HILInitialize_AOVoltages[0]
                         , &part4_open_loop_heli_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (part4_open_loop_heli_DW.HILInitialize_Card,
             part4_open_loop_heli_P.HILInitialize_analog_output_cha,
             num_final_analog_outputs,
             &part4_open_loop_heli_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm
            (part4_open_loop_heli_DW.HILInitialize_Card,
             part4_open_loop_heli_P.HILInitialize_pwm_channels,
             num_final_pwm_outputs,
             &part4_open_loop_heli_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(part4_open_loop_heli_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(part4_open_loop_heli_DW.HILInitialize_Card);
    hil_monitor_delete_all(part4_open_loop_heli_DW.HILInitialize_Card);
    hil_close(part4_open_loop_heli_DW.HILInitialize_Card);
    part4_open_loop_heli_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) part4_open_loop_heli_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "scope_data_open_loop.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(part4_open_loop_heli_M,
                          "Error closing MAT-file scope_data_open_loop.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(part4_open_loop_heli_M,
                          "Error reopening MAT-file scope_data_open_loop.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 7,
           part4_open_loop_heli_DW.ToFile1_IWORK.Count, "scope_data_open_loop"))
      {
        rtmSetErrorStatus(part4_open_loop_heli_M,
                          "Error writing header for scope_data_open_loop to MAT-file scope_data_open_loop.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(part4_open_loop_heli_M,
                          "Error closing MAT-file scope_data_open_loop.mat");
        return;
      }

      part4_open_loop_heli_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  part4_open_loop_heli_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  part4_open_loop_heli_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  part4_open_loop_heli_initialize();
}

void MdlTerminate(void)
{
  part4_open_loop_heli_terminate();
}

/* Registration function */
RT_MODEL_part4_open_loop_heli_T *part4_open_loop_heli(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  part4_open_loop_heli_P.Integrator_UpperSat = rtInf;
  part4_open_loop_heli_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)part4_open_loop_heli_M, 0,
                sizeof(RT_MODEL_part4_open_loop_heli_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&part4_open_loop_heli_M->solverInfo,
                          &part4_open_loop_heli_M->Timing.simTimeStep);
    rtsiSetTPtr(&part4_open_loop_heli_M->solverInfo, &rtmGetTPtr
                (part4_open_loop_heli_M));
    rtsiSetStepSizePtr(&part4_open_loop_heli_M->solverInfo,
                       &part4_open_loop_heli_M->Timing.stepSize0);
    rtsiSetdXPtr(&part4_open_loop_heli_M->solverInfo,
                 &part4_open_loop_heli_M->ModelData.derivs);
    rtsiSetContStatesPtr(&part4_open_loop_heli_M->solverInfo, (real_T **)
                         &part4_open_loop_heli_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&part4_open_loop_heli_M->solverInfo,
      &part4_open_loop_heli_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&part4_open_loop_heli_M->solverInfo,
                          (&rtmGetErrorStatus(part4_open_loop_heli_M)));
    rtsiSetRTModelPtr(&part4_open_loop_heli_M->solverInfo,
                      part4_open_loop_heli_M);
  }

  rtsiSetSimTimeStep(&part4_open_loop_heli_M->solverInfo, MAJOR_TIME_STEP);
  part4_open_loop_heli_M->ModelData.intgData.f[0] =
    part4_open_loop_heli_M->ModelData.odeF[0];
  part4_open_loop_heli_M->ModelData.contStates = ((real_T *)
    &part4_open_loop_heli_X);
  rtsiSetSolverData(&part4_open_loop_heli_M->solverInfo, (void *)
                    &part4_open_loop_heli_M->ModelData.intgData);
  rtsiSetSolverName(&part4_open_loop_heli_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = part4_open_loop_heli_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    part4_open_loop_heli_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    part4_open_loop_heli_M->Timing.sampleTimes =
      (&part4_open_loop_heli_M->Timing.sampleTimesArray[0]);
    part4_open_loop_heli_M->Timing.offsetTimes =
      (&part4_open_loop_heli_M->Timing.offsetTimesArray[0]);

    /* task periods */
    part4_open_loop_heli_M->Timing.sampleTimes[0] = (0.0);
    part4_open_loop_heli_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    part4_open_loop_heli_M->Timing.offsetTimes[0] = (0.0);
    part4_open_loop_heli_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(part4_open_loop_heli_M, &part4_open_loop_heli_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = part4_open_loop_heli_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    part4_open_loop_heli_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(part4_open_loop_heli_M, -1);
  part4_open_loop_heli_M->Timing.stepSize0 = 0.002;
  part4_open_loop_heli_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  part4_open_loop_heli_M->Sizes.checksums[0] = (3048316392U);
  part4_open_loop_heli_M->Sizes.checksums[1] = (356815293U);
  part4_open_loop_heli_M->Sizes.checksums[2] = (2905853496U);
  part4_open_loop_heli_M->Sizes.checksums[3] = (1652764699U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    part4_open_loop_heli_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(part4_open_loop_heli_M->extModeInfo,
      &part4_open_loop_heli_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(part4_open_loop_heli_M->extModeInfo,
                        part4_open_loop_heli_M->Sizes.checksums);
    rteiSetTPtr(part4_open_loop_heli_M->extModeInfo, rtmGetTPtr
                (part4_open_loop_heli_M));
  }

  part4_open_loop_heli_M->solverInfoPtr = (&part4_open_loop_heli_M->solverInfo);
  part4_open_loop_heli_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&part4_open_loop_heli_M->solverInfo, 0.002);
  rtsiSetSolverMode(&part4_open_loop_heli_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  part4_open_loop_heli_M->ModelData.blockIO = ((void *) &part4_open_loop_heli_B);

  {
    int_T i;
    for (i = 0; i < 6; i++) {
      part4_open_loop_heli_B.Gain1[i] = 0.0;
    }

    part4_open_loop_heli_B.TravelCounttorad = 0.0;
    part4_open_loop_heli_B.Gain = 0.0;
    part4_open_loop_heli_B.Sum3 = 0.0;
    part4_open_loop_heli_B.Gain_d = 0.0;
    part4_open_loop_heli_B.PitchCounttorad = 0.0;
    part4_open_loop_heli_B.Gain_i = 0.0;
    part4_open_loop_heli_B.Gain_b = 0.0;
    part4_open_loop_heli_B.ElevationCounttorad = 0.0;
    part4_open_loop_heli_B.Gain_e = 0.0;
    part4_open_loop_heli_B.Sum = 0.0;
    part4_open_loop_heli_B.Gain_dg = 0.0;
    part4_open_loop_heli_B.Vd_bias = 0.0;
    part4_open_loop_heli_B.Sum1 = 0.0;
    part4_open_loop_heli_B.Vs_bias = 0.0;
    part4_open_loop_heli_B.Sum2 = 0.0;
    part4_open_loop_heli_B.K_ei = 0.0;
    part4_open_loop_heli_B.Gain_l = 0.0;
    part4_open_loop_heli_B.BackmotorSaturation = 0.0;
    part4_open_loop_heli_B.FrontmotorSaturation = 0.0;
  }

  /* parameters */
  part4_open_loop_heli_M->ModelData.defaultParam = ((real_T *)
    &part4_open_loop_heli_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &part4_open_loop_heli_X;
    part4_open_loop_heli_M->ModelData.contStates = (x);
    (void) memset((void *)&part4_open_loop_heli_X, 0,
                  sizeof(X_part4_open_loop_heli_T));
  }

  /* states (dwork) */
  part4_open_loop_heli_M->ModelData.dwork = ((void *) &part4_open_loop_heli_DW);
  (void) memset((void *)&part4_open_loop_heli_DW, 0,
                sizeof(DW_part4_open_loop_heli_T));

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      part4_open_loop_heli_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      part4_open_loop_heli_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      part4_open_loop_heli_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      part4_open_loop_heli_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      part4_open_loop_heli_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      part4_open_loop_heli_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      part4_open_loop_heli_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      part4_open_loop_heli_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  part4_open_loop_heli_DW.TimeStampA = 0.0;
  part4_open_loop_heli_DW.LastUAtTimeA = 0.0;
  part4_open_loop_heli_DW.TimeStampB = 0.0;
  part4_open_loop_heli_DW.LastUAtTimeB = 0.0;
  part4_open_loop_heli_DW.HILWriteAnalog_Buffer[0] = 0.0;
  part4_open_loop_heli_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    part4_open_loop_heli_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  part4_open_loop_heli_M->Sizes.numContStates = (4);/* Number of continuous states */
  part4_open_loop_heli_M->Sizes.numY = (0);/* Number of model outputs */
  part4_open_loop_heli_M->Sizes.numU = (0);/* Number of model inputs */
  part4_open_loop_heli_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  part4_open_loop_heli_M->Sizes.numSampTimes = (2);/* Number of sample times */
  part4_open_loop_heli_M->Sizes.numBlocks = (63);/* Number of blocks */
  part4_open_loop_heli_M->Sizes.numBlockIO = (20);/* Number of block outputs */
  part4_open_loop_heli_M->Sizes.numBlockPrms = (141);/* Sum of parameter "widths" */
  return part4_open_loop_heli_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
