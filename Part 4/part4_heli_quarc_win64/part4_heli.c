/*
 * part4_heli.c
 *
 * Code generation for model "part4_heli".
 *
 * Model version              : 1.222
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Thu Mar 15 12:38:07 2018
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "part4_heli.h"
#include "part4_heli_private.h"
#include "part4_heli_dt.h"

/* Block signals (auto storage) */
B_part4_heli_T part4_heli_B;

/* Continuous states */
X_part4_heli_T part4_heli_X;

/* Block states (auto storage) */
DW_part4_heli_T part4_heli_DW;

/* Real-time model */
RT_MODEL_part4_heli_T part4_heli_M_;
RT_MODEL_part4_heli_T *const part4_heli_M = &part4_heli_M_;

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
  part4_heli_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void part4_heli_output(void)
{
  /* local block i/o variables */
  real_T rtb_FromWorkspace1[2];
  real_T rtb_Sum3_o[6];
  real_T rtb_Backgain;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_TmpSignalConversionAtToFile[2];
  real_T *lastU;
  real_T rtb_Derivative;
  int32_T i;
  int32_T i_0;
  if (rtmIsMajorTimeStep(part4_heli_M)) {
    /* set solver stop time */
    if (!(part4_heli_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&part4_heli_M->solverInfo,
                            ((part4_heli_M->Timing.clockTickH0 + 1) *
        part4_heli_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&part4_heli_M->solverInfo,
                            ((part4_heli_M->Timing.clockTick0 + 1) *
        part4_heli_M->Timing.stepSize0 + part4_heli_M->Timing.clockTickH0 *
        part4_heli_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(part4_heli_M)) {
    part4_heli_M->Timing.t[0] = rtsiGetT(&part4_heli_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(part4_heli_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: part4_heli/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(part4_heli_DW.HILReadEncoderTimebase_Task,
        1, &part4_heli_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_heli_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          part4_heli_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          part4_heli_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          part4_heli_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Travel: Count to rad' */
    part4_heli_B.TravelCounttorad = part4_heli_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;

    /* Gain: '<S12>/Gain' */
    part4_heli_B.Gain = part4_heli_P.Gain_Gain * part4_heli_B.TravelCounttorad;

    /* Sum: '<Root>/Sum3' incorporates:
     *  Constant: '<Root>/Constant'
     */
    part4_heli_B.Sum3 = part4_heli_P.x1_0 * 57.295779513082323 +
      part4_heli_B.Gain;
  }

  /* TransferFcn: '<S4>/Travel: Transfer Fcn' */
  rtb_Backgain = 0.0;
  rtb_Backgain += part4_heli_P.TravelTransferFcn_C *
    part4_heli_X.TravelTransferFcn_CSTATE;
  rtb_Backgain += part4_heli_P.TravelTransferFcn_D *
    part4_heli_B.TravelCounttorad;

  /* Gain: '<S13>/Gain' */
  part4_heli_B.Gain_d = part4_heli_P.Gain_Gain_l * rtb_Backgain;
  if (rtmIsMajorTimeStep(part4_heli_M)) {
    /* Gain: '<S4>/Pitch: Count to rad' */
    part4_heli_B.PitchCounttorad = part4_heli_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S9>/Gain' */
    part4_heli_B.Gain_i = part4_heli_P.Gain_Gain_a *
      part4_heli_B.PitchCounttorad;
  }

  /* TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  rtb_Backgain = 0.0;
  rtb_Backgain += part4_heli_P.PitchTransferFcn_C *
    part4_heli_X.PitchTransferFcn_CSTATE;
  rtb_Backgain += part4_heli_P.PitchTransferFcn_D * part4_heli_B.PitchCounttorad;

  /* Gain: '<S10>/Gain' */
  part4_heli_B.Gain_b = part4_heli_P.Gain_Gain_ae * rtb_Backgain;
  if (rtmIsMajorTimeStep(part4_heli_M)) {
    /* Gain: '<S4>/Elevation: Count to rad' */
    part4_heli_B.ElevationCounttorad = part4_heli_P.ElevationCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o3;

    /* Gain: '<S7>/Gain' */
    part4_heli_B.Gain_e = part4_heli_P.Gain_Gain_lv *
      part4_heli_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    part4_heli_B.Sum = part4_heli_B.Gain_e +
      part4_heli_P.elavation_offsetdeg_Value;
  }

  /* TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  rtb_Backgain = 0.0;
  rtb_Backgain += part4_heli_P.ElevationTransferFcn_C *
    part4_heli_X.ElevationTransferFcn_CSTATE;
  rtb_Backgain += part4_heli_P.ElevationTransferFcn_D *
    part4_heli_B.ElevationCounttorad;

  /* Gain: '<S8>/Gain' */
  part4_heli_B.Gain_dg = part4_heli_P.Gain_Gain_n * rtb_Backgain;

  /* Gain: '<S2>/Gain1' */
  part4_heli_B.Gain1[0] = part4_heli_P.Gain1_Gain * part4_heli_B.Sum3;
  part4_heli_B.Gain1[1] = part4_heli_P.Gain1_Gain * part4_heli_B.Gain_d;
  part4_heli_B.Gain1[2] = part4_heli_P.Gain1_Gain * part4_heli_B.Gain_i;
  part4_heli_B.Gain1[3] = part4_heli_P.Gain1_Gain * part4_heli_B.Gain_b;
  part4_heli_B.Gain1[4] = part4_heli_P.Gain1_Gain * part4_heli_B.Sum;
  part4_heli_B.Gain1[5] = part4_heli_P.Gain1_Gain * part4_heli_B.Gain_dg;

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *) part4_heli_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) part4_heli_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = part4_heli_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = part4_heli_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[140]) {
      currTimeIndex = 139;
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

    part4_heli_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_Sum3_o[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 141;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_Sum3_o[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 141;
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
          for (elIdx = 0; elIdx < 6; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_Sum3_o[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 141;
          }
        }
      }
    }
  }

  /* Sum: '<S5>/Sum3' */
  for (i = 0; i < 6; i++) {
    rtb_Sum3_o[i] = part4_heli_B.Gain1[i] - rtb_Sum3_o[i];
  }

  /* End of Sum: '<S5>/Sum3' */

  /* FromWorkspace: '<Root>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *) part4_heli_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) part4_heli_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = part4_heli_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = part4_heli_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[140]) {
      currTimeIndex = 139;
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

    part4_heli_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_FromWorkspace1[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 141;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_FromWorkspace1[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 141;
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
            (&rtb_FromWorkspace1[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1,
              f2);
            pDataValues += 141;
          }
        }
      }
    }
  }

  /* Sum: '<S5>/Sum1' incorporates:
   *  Gain: '<S5>/Gain'
   */
  for (i = 0; i < 2; i++) {
    rtb_Derivative = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Derivative += part4_heli_P.K[(i_0 << 1) + i] * rtb_Sum3_o[i_0];
    }

    part4_heli_B.Sum1[i] = rtb_FromWorkspace1[i] - rtb_Derivative;
  }

  /* End of Sum: '<S5>/Sum1' */
  if (rtmIsMajorTimeStep(part4_heli_M)) {
    /* SignalConversion: '<Root>/TmpSignal ConversionAtTo FileInport1' */
    rtb_TmpSignalConversionAtToFile[0] = part4_heli_B.Sum1[0];
    rtb_TmpSignalConversionAtToFile[1] = part4_heli_B.Gain1[2];

    /* ToFile: '<Root>/To File' */
    {
      if (!(++part4_heli_DW.ToFile_IWORK.Decimation % 1) &&
          (part4_heli_DW.ToFile_IWORK.Count*3)+1 < 100000000 ) {
        FILE *fp = (FILE *) part4_heli_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[3];
          part4_heli_DW.ToFile_IWORK.Decimation = 0;
          u[0] = part4_heli_M->Timing.t[1];
          u[1] = rtb_TmpSignalConversionAtToFile[0];
          u[2] = rtb_TmpSignalConversionAtToFile[1];
          if (fwrite(u, sizeof(real_T), 3, fp) != 3) {
            rtmSetErrorStatus(part4_heli_M,
                              "Error writing to MAT-file pitch_data.mat");
            return;
          }

          if (((++part4_heli_DW.ToFile_IWORK.Count)*3)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file pitch_data.mat.\n");
          }
        }
      }
    }

    /* ToFile: '<Root>/To File1' */
    {
      if (!(++part4_heli_DW.ToFile1_IWORK.Decimation % 1) &&
          (part4_heli_DW.ToFile1_IWORK.Count*7)+1 < 100000000 ) {
        FILE *fp = (FILE *) part4_heli_DW.ToFile1_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[7];
          part4_heli_DW.ToFile1_IWORK.Decimation = 0;
          u[0] = part4_heli_M->Timing.t[1];
          u[1] = part4_heli_B.Gain1[0];
          u[2] = part4_heli_B.Gain1[1];
          u[3] = part4_heli_B.Gain1[2];
          u[4] = part4_heli_B.Gain1[3];
          u[5] = part4_heli_B.Gain1[4];
          u[6] = part4_heli_B.Gain1[5];
          if (fwrite(u, sizeof(real_T), 7, fp) != 7) {
            rtmSetErrorStatus(part4_heli_M,
                              "Error writing to MAT-file scope_data.mat");
            return;
          }

          if (((++part4_heli_DW.ToFile1_IWORK.Count)*7)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file scope_data.mat.\n");
          }
        }
      }
    }

    /* SignalConversion: '<Root>/TmpSignal ConversionAtTo File2Inport1' */
    rtb_TmpSignalConversionAtToFile[0] = part4_heli_B.Sum1[1];
    rtb_TmpSignalConversionAtToFile[1] = part4_heli_B.Gain1[4];

    /* ToFile: '<Root>/To File2' */
    {
      if (!(++part4_heli_DW.ToFile2_IWORK.Decimation % 1) &&
          (part4_heli_DW.ToFile2_IWORK.Count*3)+1 < 100000000 ) {
        FILE *fp = (FILE *) part4_heli_DW.ToFile2_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[3];
          part4_heli_DW.ToFile2_IWORK.Decimation = 0;
          u[0] = part4_heli_M->Timing.t[1];
          u[1] = rtb_TmpSignalConversionAtToFile[0];
          u[2] = rtb_TmpSignalConversionAtToFile[1];
          if (fwrite(u, sizeof(real_T), 3, fp) != 3) {
            rtmSetErrorStatus(part4_heli_M,
                              "Error writing to MAT-file elev_data.mat");
            return;
          }

          if (((++part4_heli_DW.ToFile2_IWORK.Count)*3)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file elev_data.mat.\n");
          }
        }
      }
    }

    /* Constant: '<Root>/Vd_bias' */
    part4_heli_B.Vd_bias = part4_heli_P.Vd_ff;
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Gain: '<S6>/K_pd'
   *  Gain: '<S6>/K_pp'
   *  Sum: '<S6>/Sum2'
   *  Sum: '<S6>/Sum3'
   */
  part4_heli_B.Sum1_c = ((part4_heli_B.Sum1[0] - part4_heli_B.Gain1[2]) *
    part4_heli_P.K_pp - part4_heli_P.K_pd * part4_heli_B.Gain1[3]) +
    part4_heli_B.Vd_bias;
  if (rtmIsMajorTimeStep(part4_heli_M)) {
  }

  /* Integrator: '<S3>/Integrator'
   *
   * Regarding '<S3>/Integrator':
   *  Limited Integrator
   */
  if (part4_heli_X.Integrator_CSTATE >= part4_heli_P.Integrator_UpperSat ) {
    part4_heli_X.Integrator_CSTATE = part4_heli_P.Integrator_UpperSat;
  } else if (part4_heli_X.Integrator_CSTATE <= (part4_heli_P.Integrator_LowerSat)
             ) {
    part4_heli_X.Integrator_CSTATE = (part4_heli_P.Integrator_LowerSat);
  }

  rtb_Backgain = part4_heli_X.Integrator_CSTATE;

  /* Sum: '<S3>/Sum' */
  rtb_Derivative = part4_heli_B.Sum1[1] - part4_heli_B.Gain1[4];
  if (rtmIsMajorTimeStep(part4_heli_M)) {
    /* Constant: '<Root>/Vs_bias' */
    part4_heli_B.Vs_bias = part4_heli_P.Vs_ff;
  }

  /* Sum: '<Root>/Sum2' incorporates:
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Sum: '<S3>/Sum1'
   */
  part4_heli_B.Sum2 = ((part4_heli_P.K_ep * rtb_Derivative + rtb_Backgain) -
                       part4_heli_P.K_ed * part4_heli_B.Gain1[5]) +
    part4_heli_B.Vs_bias;
  if (rtmIsMajorTimeStep(part4_heli_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Backgain = (part4_heli_B.Sum2 - part4_heli_B.Sum1_c) *
    part4_heli_P.Backgain_Gain;

  /* Gain: '<S3>/K_ei' */
  part4_heli_B.K_ei = part4_heli_P.K_ei * rtb_Derivative;
  if (rtmIsMajorTimeStep(part4_heli_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  if ((part4_heli_DW.TimeStampA >= part4_heli_M->Timing.t[0]) &&
      (part4_heli_DW.TimeStampB >= part4_heli_M->Timing.t[0])) {
    rtb_Derivative = 0.0;
  } else {
    rtb_Derivative = part4_heli_DW.TimeStampA;
    lastU = &part4_heli_DW.LastUAtTimeA;
    if (part4_heli_DW.TimeStampA < part4_heli_DW.TimeStampB) {
      if (part4_heli_DW.TimeStampB < part4_heli_M->Timing.t[0]) {
        rtb_Derivative = part4_heli_DW.TimeStampB;
        lastU = &part4_heli_DW.LastUAtTimeB;
      }
    } else {
      if (part4_heli_DW.TimeStampA >= part4_heli_M->Timing.t[0]) {
        rtb_Derivative = part4_heli_DW.TimeStampB;
        lastU = &part4_heli_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (part4_heli_B.PitchCounttorad - *lastU) /
      (part4_heli_M->Timing.t[0] - rtb_Derivative);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S11>/Gain' */
  part4_heli_B.Gain_l = part4_heli_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(part4_heli_M)) {
  }

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Backgain > part4_heli_P.BackmotorSaturation_UpperSat) {
    part4_heli_B.BackmotorSaturation = part4_heli_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Backgain < part4_heli_P.BackmotorSaturation_LowerSat) {
    part4_heli_B.BackmotorSaturation = part4_heli_P.BackmotorSaturation_LowerSat;
  } else {
    part4_heli_B.BackmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(part4_heli_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Derivative = (part4_heli_B.Sum1_c + part4_heli_B.Sum2) *
    part4_heli_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Derivative > part4_heli_P.FrontmotorSaturation_UpperSat) {
    part4_heli_B.FrontmotorSaturation =
      part4_heli_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Derivative < part4_heli_P.FrontmotorSaturation_LowerSat) {
    part4_heli_B.FrontmotorSaturation =
      part4_heli_P.FrontmotorSaturation_LowerSat;
  } else {
    part4_heli_B.FrontmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(part4_heli_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: part4_heli/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      part4_heli_DW.HILWriteAnalog_Buffer[0] = part4_heli_B.FrontmotorSaturation;
      part4_heli_DW.HILWriteAnalog_Buffer[1] = part4_heli_B.BackmotorSaturation;
      result = hil_write_analog(part4_heli_DW.HILInitialize_Card,
        part4_heli_P.HILWriteAnalog_channels, 2,
        &part4_heli_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_heli_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void part4_heli_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (part4_heli_DW.TimeStampA == (rtInf)) {
    part4_heli_DW.TimeStampA = part4_heli_M->Timing.t[0];
    lastU = &part4_heli_DW.LastUAtTimeA;
  } else if (part4_heli_DW.TimeStampB == (rtInf)) {
    part4_heli_DW.TimeStampB = part4_heli_M->Timing.t[0];
    lastU = &part4_heli_DW.LastUAtTimeB;
  } else if (part4_heli_DW.TimeStampA < part4_heli_DW.TimeStampB) {
    part4_heli_DW.TimeStampA = part4_heli_M->Timing.t[0];
    lastU = &part4_heli_DW.LastUAtTimeA;
  } else {
    part4_heli_DW.TimeStampB = part4_heli_M->Timing.t[0];
    lastU = &part4_heli_DW.LastUAtTimeB;
  }

  *lastU = part4_heli_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(part4_heli_M)) {
    rt_ertODEUpdateContinuousStates(&part4_heli_M->solverInfo);
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
  if (!(++part4_heli_M->Timing.clockTick0)) {
    ++part4_heli_M->Timing.clockTickH0;
  }

  part4_heli_M->Timing.t[0] = rtsiGetSolverStopTime(&part4_heli_M->solverInfo);

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
    if (!(++part4_heli_M->Timing.clockTick1)) {
      ++part4_heli_M->Timing.clockTickH1;
    }

    part4_heli_M->Timing.t[1] = part4_heli_M->Timing.clockTick1 *
      part4_heli_M->Timing.stepSize1 + part4_heli_M->Timing.clockTickH1 *
      part4_heli_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void part4_heli_derivatives(void)
{
  XDot_part4_heli_T *_rtXdot;
  _rtXdot = ((XDot_part4_heli_T *) part4_heli_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += part4_heli_P.TravelTransferFcn_A *
    part4_heli_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += part4_heli_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += part4_heli_P.PitchTransferFcn_A *
    part4_heli_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += part4_heli_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += part4_heli_P.ElevationTransferFcn_A *
    part4_heli_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += part4_heli_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  {
    boolean_T lsat;
    boolean_T usat;
    lsat = ( part4_heli_X.Integrator_CSTATE <= (part4_heli_P.Integrator_LowerSat)
            );
    usat = ( part4_heli_X.Integrator_CSTATE >= part4_heli_P.Integrator_UpperSat );
    if ((!lsat && !usat) ||
        (lsat && (part4_heli_B.K_ei > 0)) ||
        (usat && (part4_heli_B.K_ei < 0)) ) {
      ((XDot_part4_heli_T *) part4_heli_M->ModelData.derivs)->Integrator_CSTATE =
        part4_heli_B.K_ei;
    } else {
      /* in saturation */
      ((XDot_part4_heli_T *) part4_heli_M->ModelData.derivs)->Integrator_CSTATE =
        0.0;
    }
  }
}

/* Model initialize function */
void part4_heli_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: part4_heli/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &part4_heli_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(part4_heli_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(part4_heli_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(part4_heli_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(part4_heli_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(part4_heli_M, _rt_error_message);
      return;
    }

    if ((part4_heli_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (part4_heli_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &part4_heli_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = part4_heli_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &part4_heli_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = part4_heli_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(part4_heli_DW.HILInitialize_Card,
        part4_heli_P.HILInitialize_analog_input_chan, 8U,
        &part4_heli_DW.HILInitialize_AIMinimums[0],
        &part4_heli_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_heli_M, _rt_error_message);
        return;
      }
    }

    if ((part4_heli_P.HILInitialize_set_analog_output && !is_switching) ||
        (part4_heli_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &part4_heli_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = part4_heli_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &part4_heli_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = part4_heli_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges(part4_heli_DW.HILInitialize_Card,
        part4_heli_P.HILInitialize_analog_output_cha, 8U,
        &part4_heli_DW.HILInitialize_AOMinimums[0],
        &part4_heli_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_heli_M, _rt_error_message);
        return;
      }
    }

    if ((part4_heli_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (part4_heli_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &part4_heli_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = part4_heli_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(part4_heli_DW.HILInitialize_Card,
        part4_heli_P.HILInitialize_analog_output_cha, 8U,
        &part4_heli_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_heli_M, _rt_error_message);
        return;
      }
    }

    if (part4_heli_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &part4_heli_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = part4_heli_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (part4_heli_DW.HILInitialize_Card,
         part4_heli_P.HILInitialize_analog_output_cha, 8U,
         &part4_heli_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_heli_M, _rt_error_message);
        return;
      }
    }

    if ((part4_heli_P.HILInitialize_set_encoder_param && !is_switching) ||
        (part4_heli_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &part4_heli_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = part4_heli_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(part4_heli_DW.HILInitialize_Card,
        part4_heli_P.HILInitialize_encoder_channels, 8U,
        (t_encoder_quadrature_mode *)
        &part4_heli_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_heli_M, _rt_error_message);
        return;
      }
    }

    if ((part4_heli_P.HILInitialize_set_encoder_count && !is_switching) ||
        (part4_heli_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &part4_heli_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = part4_heli_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(part4_heli_DW.HILInitialize_Card,
        part4_heli_P.HILInitialize_encoder_channels, 8U,
        &part4_heli_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_heli_M, _rt_error_message);
        return;
      }
    }

    if ((part4_heli_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (part4_heli_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &part4_heli_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = part4_heli_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(part4_heli_DW.HILInitialize_Card,
        part4_heli_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &part4_heli_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_heli_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          part4_heli_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues = &part4_heli_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            part4_heli_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              p_HILInitialize_pwm_channels[i1];
            part4_heli_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              part4_heli_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            part4_heli_DW.HILInitialize_POSortedChans[7U - num_frequency_modes] =
              p_HILInitialize_pwm_channels[i1];
            part4_heli_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes] =
              part4_heli_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(part4_heli_DW.HILInitialize_Card,
          &part4_heli_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &part4_heli_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(part4_heli_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(part4_heli_DW.HILInitialize_Card,
          &part4_heli_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &part4_heli_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(part4_heli_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &part4_heli_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = part4_heli_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &part4_heli_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = part4_heli_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &part4_heli_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = part4_heli_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(part4_heli_DW.HILInitialize_Card,
        part4_heli_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &part4_heli_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &part4_heli_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &part4_heli_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_heli_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &part4_heli_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = part4_heli_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &part4_heli_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = part4_heli_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(part4_heli_DW.HILInitialize_Card,
        part4_heli_P.HILInitialize_pwm_channels, 8U,
        &part4_heli_DW.HILInitialize_POSortedFreqs[0],
        &part4_heli_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_heli_M, _rt_error_message);
        return;
      }
    }

    if ((part4_heli_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (part4_heli_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &part4_heli_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = part4_heli_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(part4_heli_DW.HILInitialize_Card,
        part4_heli_P.HILInitialize_pwm_channels, 8U,
        &part4_heli_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_heli_M, _rt_error_message);
        return;
      }
    }

    if (part4_heli_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &part4_heli_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = part4_heli_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (part4_heli_DW.HILInitialize_Card,
         part4_heli_P.HILInitialize_pwm_channels, 8U,
         &part4_heli_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(part4_heli_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: part4_heli/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(part4_heli_DW.HILInitialize_Card,
      part4_heli_P.HILReadEncoderTimebase_samples_,
      part4_heli_P.HILReadEncoderTimebase_channels, 3,
      &part4_heli_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(part4_heli_M, _rt_error_message);
    }
  }

  /* Start for FromWorkspace: '<Root>/From Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1378421413625261, 3.1262155534579983,
      3.1033093000299643, 3.0666274151911783, 3.0144539223941584,
      2.9456562771175667, 2.8595077632935446, 2.7555515879651526,
      2.633505110490284, 2.4931956060320961, 2.334518576064299,
      2.1574113214711188, 1.9618364840294067, 1.7516020860978305,
      1.5345791276663521, 1.3182737819604318, 1.1085618620311131,
      0.90963614483384192, 0.72433125157166822, 0.55449695053892445,
      0.4013105139454537, 0.26550738631304777, 0.14754043177220028,
      0.047685328898611962, -0.033891667273920525, -0.097091068977370409,
      -0.14185373181463173, -0.16814469199871598, -0.17739522460515691,
      -0.17248849758716092, -0.15710579443763395, -0.13505523530146563,
      -0.10978406875072716, -0.084101008028563809, -0.060071932308128809,
      -0.039037091105793779, -0.021701963922708074, -0.00826426148939439,
      0.0014498072798965291, 0.00785761081154581, 0.011510315082354406,
      0.013005905121014681, 0.012925481779116675, 0.011791090913377223,
      0.010041880872693545, 0.0080247218014526216, 0.0059955116883692325,
      0.0041275921436499706, 0.0025242304489266785, 0.0012329239607059878,
      0.00025962795556815039, -0.00041813290041525596, -0.00084015785813127818,
      -0.00105458993446665, -0.0011111939613524639, -0.0010566724543202397,
      -0.00093178761998110628, -0.00076987217119478069, -0.00059648476573494679,
      -0.00042981365977325607, -0.0002815718912651358, -0.00015814497413132463,
      -6.1729298400315286E-5, 8.4257017735851118E-6, 5.500132140403631E-5,
      8.1790103847072165E-5, 9.2978434646610333E-5, 9.268433563763537E-5,
      8.4671393911468442E-5, 7.2114174476966357E-5, 5.75572644609105E-5,
      4.290832062645034E-5, 2.9454842568852507E-5, 1.7954260265604249E-5,
      8.7728927690687772E-6, 1.9420848160925582E-6, -2.7157375216371062E-6,
      -5.5024488768246441E-6, -6.7930432082939849E-6, -7.0083770138360131E-6,
      -6.5276277779534976E-6, -5.6545592001898864E-6, -4.6158646529006284E-6,
      -3.5946343626154332E-6, -2.6840499161341822E-6, -1.9572159955022755E-6,
      -1.4205840309786397E-6, -1.0895777556223244E-6, -9.1086778194136738E-7,
      -8.2017229409382147E-7, -7.6645451788055222E-7, -7.2291089418180992E-7,
      -6.8319372066095173E-7, -6.29226503949369E-7, -5.6961011151907435E-7,
      -5.1628991015093584E-7, -4.7798415749434329E-7, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.015002048909068423,
      -0.046506351618112111, -0.091625013712135384, -0.14672753935514371,
      -0.20869397118807925, -0.27519058110636674, -0.34459405529608839,
      -0.41582470131356869, -0.48818590989947463, -0.56123801783275185,
      -0.63470811987118858, -0.7084290183727211, -0.78229934976684812,
      -0.84093759172630433, -0.86809183372591436, -0.86522138282368144,
      -0.8388476797172747, -0.79570286878908447, -0.74121957304869479,
      -0.6793372041309752, -0.61274574637388313, -0.5432125105296236,
      -0.47186781816339007, -0.39942041149435326, -0.32630798469012995,
      -0.25279760681379954, -0.17905065134904524, -0.10516384073633701,
      -0.037002130425763724, 0.019626908071984018, 0.061530812598107817,
      0.088202236544673365, 0.10108466620295387, 0.10273224288865337,
      0.096116302881740015, 0.084139364809340131, 0.06934050873234282,
      0.053750809733254731, 0.038856275077163674, 0.025631214126597128,
      0.014610817083234386, 0.0059823601546410976, -0.00032169336759202676,
      -0.0045375634629578037, -0.0069968401627347153, -0.00806863628496369,
      -0.0081168404523335579, -0.0074716781788770458, -0.0064134467788931719,
      -0.0051652259528827621, -0.0038931840205513493, -0.0027110434239336254,
      -0.0016880998308640887, -0.0008577283053414871, -0.00022641610754325578,
      0.00021808602812889734, 0.00049953933735653335, 0.00064766179514530258,
      0.00069354962183933578, 0.00066668442384676288, 0.000592967074032481,
      0.00049370766853524476, 0.00038566270292403739, 0.0002806200006956016,
      0.00018630247852180482, 0.00010715512977214343, 4.4753323198152652E-5,
      -1.1763960358998378E-6, -3.2051766904667709E-5, -5.0228877738008341E-5,
      -5.8227640064223421E-5, -5.8595775337840626E-5, -5.3813912230391352E-5,
      -4.6002329212993026E-5, -3.6725469986141894E-5, -2.7323231811904879E-5,
      -1.8631289350918647E-5, -1.1146845420750152E-5, -5.1623773258773708E-6,
      -8.6133522216809685E-7, 1.9229969435300513E-6, 3.4922743110544423E-6,
      4.154778189157034E-6, 4.0849211611407807E-6, 3.6423377859250053E-6,
      2.9073356825276191E-6, 2.1465278580945464E-6, 1.3240251014252582E-6,
      7.1483989472383137E-7, 3.62781951390185E-7, 2.1487110485307965E-7,
      1.741744947949657E-7, 1.5886869408343202E-7, 2.1586886684633161E-7,
      2.3846556972117869E-7, 2.1328080547255081E-7, 1.5322301062636986E-7,
      1.5262664809790809E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.10602875205865551, 0.22266037932317656, 0.31888147181640641,
      0.38944360631144165, 0.43795507377677839, 0.46997264230390062,
      0.4905172487754707, 0.5034310014147434, 0.5114213858602934,
      0.51630439857701838, 0.51925862127063693, 0.52103115488680807,
      0.52208728949977667, 0.41443269886397882, 0.19191581161803875,
      -0.0202872506851665, -0.18639926082679537, -0.30493104563586754,
      -0.38506712585800418, -0.43736094919761015, -0.47064299060398046,
      -0.49143435459075696, -0.50423703745078408, -0.512030600990814,
      -0.51673070931968879, -0.51954327551059187, -0.52121531555110079,
      -0.52220375832291233, -0.48174093593609391, -0.40023241615805405,
      -0.29616079311701488, -0.18850343801854005, -0.0910480927258697,
      -0.011644442766751554, 0.046758937187834845, 0.084648424025116478,
      0.10459266272563507, 0.11018203845770716, 0.10526888238079986,
      0.093469679840905276, 0.077887957357099885, 0.06098263816335045,
      0.044554642630801555, 0.029796159695415613, 0.017381228459177629,
      0.0075750456481014855, 0.0003406886446800059, -0.0045597605463457242,
      -0.0074791753719553452, -0.0088219480737398975, -0.0089903065553834163,
      -0.008354918249965565, -0.0072297746299172143, -0.0058687488042372116,
      -0.0044618735012583108, -0.0031415713292493315, -0.0019892044960702782,
      -0.0010468729602468232, -0.00032431763344746551, 0.00018987295896891464,
      0.000521006074120646, 0.00070152756858393272, 0.00076362055206018089,
      0.000742401701104813, 0.000666600224673793, 0.00055938323275329807,
      0.00044103213616683936, 0.00032461371392058841, 0.00021821532927977292,
      0.00012846887710957704, 5.6532197208723588E-5, 2.6018395145219284E-6,
      -3.379638213895515E-5, -5.5209285342128831E-5, -6.55652979675513E-5,
      -6.6451428482544982E-5, -6.1431329659705623E-5, -5.2897191215597913E-5,
      -4.2295934887310166E-5, -3.0398122921220836E-5, -1.9678596346082731E-5,
      -1.1091053090216552E-5, -4.6823243848229276E-6, 4.9372279399864827E-7,
      3.1280102631628078E-6, 5.1947141524517931E-6, 5.3770991329282672E-6,
      5.8131353512474373E-6, 4.3054883789975156E-6, 2.4882110843832292E-6,
      1.0453773727393131E-6, 2.8762809691089454E-7, 1.08175553788613E-7,
      -4.0285545139935217E-7, -1.5970486571417678E-7, 1.7799629506335133E-7,
      4.2446555650715983E-7, 4.2148625864813948E-9, 1.0251487380220639E-6, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.42411500823462206,
      0.46652650905808424, 0.38488436997291947, 0.28224853798014093,
      0.19404586986134692, 0.12807027410848898, 0.082178425886280479,
      0.051655010557090625, 0.031961537782199817, 0.019532050866899898,
      0.011816890774474453, 0.0070901344646846411, 0.0042245384518745915,
      -0.43061836254319152, -0.89006754898376039, -0.848812249212821,
      -0.66444804056651552, -0.47412713923628869, -0.32054432088854667,
      -0.20917529335842402, -0.13312816562548105, -0.083165455947105935,
      -0.051210731440108459, -0.031174254160119739, -0.01880043331549891,
      -0.011250264763612577, -0.00668816016203538, -0.0039537710872460984,
      0.1618512895472736, 0.32603407911215954, 0.41628649216415659,
      0.4306294203938994, 0.38982138117068144, 0.31761459983647256,
      0.23361351981834561, 0.15155794734912653, 0.079776954802074376,
      0.022357502928288368, -0.019652624307629228, -0.047196810159578315,
      -0.062326889935221549, -0.067621276774997727, -0.065711982130195593,
      -0.059033931741543776, -0.049659724944951932, -0.039224731244304568,
      -0.028937428013685918, -0.019601796764102921, -0.011677659302438479,
      -0.005371090807138215, -0.00067343392657406886, 0.0025415532216714041,
      0.0045005744801934026, 0.005444103302720011, 0.0056275012119156023,
      0.0052812086880359181, 0.004609467332716213, 0.0037693261432938207,
      0.00289022130719743, 0.0020567623696655206, 0.0013245324606069257,
      0.00072208597785314668, 0.00024837193390499245, -8.4875403821470867E-5,
      -0.00030320590572408012, -0.0004288679676819794, -0.00047340438634583512,
      -0.00046567368898500381, -0.00042559353856326185, -0.00035898580868078356,
      -0.00028774671960341382, -0.00021572143077680663, -0.00014559288661390832,
      -8.5651612812694724E-5, -4.1424050501689841E-5, -3.5445220599747488E-6,
      2.0080395291357451E-5, 3.4136553776430839E-5, 4.2405025313151E-5,
      4.7591247864357327E-5, 4.2878106300552418E-5, 3.4350173023464711E-5,
      2.5634914821574497E-5, 2.0704188715286304E-5, 1.0537149876656639E-5,
      8.2668155571559411E-6, 7.2953992190590294E-7, 1.7441448732766772E-6,
      -6.030587888999684E-6, -7.2691091784571492E-6, -5.7713348465756611E-6,
      -3.0309971033136737E-6, -7.1781017248912615E-7, -2.044124020751859E-6,
      9.7260234274070113E-7, 1.3508046431101116E-6, 9.8587704577523633E-7,
      -1.6810027756827137E-6, 4.0837355017423315E-6, 1.680995798431067E-6, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0044743445848396289, 0.012578339298050811, 0.023595598676071132,
      0.03690967533185914, 0.051978571646550016, 0.06831145365560326,
      0.085445803294535522, 0.10292610141119624, 0.12028181986641685,
      0.13700522376388738, 0.15252763999503038, 0.1661938525700051,
      0.17723369241217748, 0.18473021976231932, 0.18758332818807916,
      0.18683675545642897, 0.18334585101470485, 0.17780827818272019,
      0.17079040934185127, 0.16274875807204148, 0.15404885446818961,
      0.14498101617738446, 0.13577316288966002, 0.12660188007041898,
      0.11760203728541836, 0.10887398583865703, 0.10049048453009146,
      0.092501760122729315, 0.084940040408267983, 0.077823344094653232,
      0.071158592305285387, 0.064943988794737714, 0.059171140764950933,
      0.053826743113680839, 0.048893870313338771, 0.044353247081908881,
      0.040183889330824216, 0.036363912366449633, 0.032871122532630907,
      0.029683415265371448, 0.02677894835523292, 0.024136810740679884,
      0.021736859741435136, 0.01955970588610614, 0.017587258550352595,
      0.015802333929663522, 0.01418881168807218, 0.012731806511945668,
      0.011417366107966471, 0.01023261416989108, 0.0091657381819134718,
      0.0082056398540291918, 0.0073424560115096143, 0.00656693060181082,
      0.0058706515781941655, 0.0052457677230527133, 0.004685319274999088,
      0.004183010010573994, 0.0037329990727298129, 0.0033302139093396685,
      0.0029698257875111814, 0.0026475674164165683, 0.0023594849891674279,
      0.0021020373025739214, 0.001872088553099703, 0.0016667637436387737,
      0.0014835445563452134, 0.0013201024431609271, 0.0011743272134225311,
      0.0010443786289223249, 0.00092855307430063112, 0.00082535536109928735,
      0.00073349076750124469, 0.00065170224665384653, 0.000578991840789029,
      0.00051427436392018707, 0.00045668919131170544, 0.00040552217367765197,
      0.000360045390118424, 0.0003196349245213165, 0.00028375539634320821,
      0.00025185975069788954, 0.00022352484438591848, 0.00019833799801139234,
      0.00017594479144075327, 0.00015602258971226626, 0.00013839888723540084,
      0.00012270283320494813, 0.00010872297265663294, 9.6286308001101517E-5,
      8.5274379099597536E-5, 7.5601777359304E-5, 6.7007370299719345E-5,
      5.9411450251594869E-5, 5.2725123232707365E-5, 4.6730938732397935E-5,
      4.13734471365936E-5, 3.6581361789385E-5, 3.2257186934201781E-5, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.017897378339358515,
      0.032415978852844723, 0.044069037512081286, 0.053256306623152061,
      0.060275585258763489, 0.065331528036212963, 0.068537398555729032,
      0.06992119246664287, 0.069422873820882455, 0.066893615589882091,
      0.062089664924572005, 0.054664850299898905, 0.044159359368689463,
      0.029986109400567406, 0.01141243370303935, -0.00298629092660079,
      -0.013963617766896362, -0.022150291327938672, -0.028071475363475634,
      -0.032166605079239179, -0.034799614415407576, -0.036271353163220485,
      -0.036831413150897829, -0.036685131276964156, -0.03599937114000247,
      -0.034912205787045354, -0.033534005234262219, -0.031954897629448586,
      -0.03024687885784532, -0.028466785254458997, -0.026659007157471392,
      -0.024858414042190705, -0.023091392119147146, -0.021377590605080359,
      -0.01973149120136828, -0.018162492925719531, -0.016677431004338664,
      -0.015279907857498316, -0.013971159335274897, -0.012750829069037829,
      -0.01161786764055411, -0.010568550458212143, -0.0095998039969789912,
      -0.008708615421315985, -0.0078897893430141842, -0.0071396984827563,
      -0.00645408896636536, -0.0058280207045060487, -0.0052577616159167886,
      -0.00473900775230157, -0.0042675039519104304, -0.0038403933115371209,
      -0.003452735370078308, -0.0031021016387951781, -0.0027851160944666197,
      -0.0024995354205658064, -0.0022417937922145025, -0.0020092370577003758,
      -0.0018000437513767252, -0.0016111406535605768, -0.0014415524873139483,
      -0.0012890334843784525, -0.0011523297089965612, -0.0010297907463740271,
      -0.00091979499789687346, -0.00082129923784371743, -0.00073287674917424091,
      -0.00065376845273714583, -0.00058310091895358361, -0.00051979433800082467,
      -0.00046330221848677556, -0.000412790852805375, -0.00036745837439217073,
      -0.00032715408338959283, -0.00029084162345927023, -0.00025886990747536775,
      -0.00023034069043392636, -0.00020466807053621408, -0.00018190713423691215,
      -0.00016164186238842984, -0.00014351811271243311, -0.00012758258258127475,
      -0.00011333962524788414, -0.00010074738549810461, -8.9572826282556146E-5,
      -7.9688806913948162E-5, -7.0494809907461592E-5, -6.2784216121810946E-5,
      -5.5919442193260759E-5, -4.9746658622125643E-5, -4.4047715606015959E-5,
      -3.86904069611741E-5, -3.43776282383386E-5, -3.0383680192497928E-5,
      -2.6745308075550014E-5, -2.3976738001237719E-5, -2.1429966383217333E-5,
      -1.9168341388834411E-5, -1.7296699420732877E-5, -1.5196077828147879E-5,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0 } ;

    part4_heli_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    part4_heli_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    part4_heli_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace1' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      -0.011118001148227648, -0.52359877559829882, -0.52359877559829882,
      -0.52359877559829882, -0.52359877559829882, -0.52359877559829882,
      -0.52359877559829882, -0.52359877559829882, -0.52359877559829882,
      -0.52359877559829882, -0.52359877559829882, -0.52359877559829882,
      -0.52359877559829882, -0.52359877559829882, -0.52359877559829882,
      -0.32091078881530044, -0.13967419022731711, -0.0080581158707350529,
      0.080015449493160473, 0.13193604531667827, 0.15548725546220615,
      0.15815198114412826, 0.1466229589212632, 0.12653814714729378,
      0.10240127272645096, 0.077569978033711545, 0.054340621508552366,
      0.034148871369363169, 0.017681299863774952, 0.00511035926735196,
      -0.0037861686619880862, -0.0094655200491954288, -0.012498604193237933,
      -0.013501431897927883, -0.013052181466385341, -0.011656199782515288,
      -0.0097490505178202524, -0.0076474776507951571, -0.0056010880560500081,
      -0.0037478137676966714, -0.0021894295404585656, -0.00095435378838190372,
      -4.3491314305906721E-5, 0.00057682583690541833, 0.00094284769546943315,
      0.0011136210506803984, 0.001135522396476359, 0.0010569863463554647,
      0.00091781460315712958, 0.00073849167426839641, 0.00056607991770495731,
      0.00039977071830470806, 0.00025036790220410774, 0.00013509702766436441,
      4.2922429851544679E-5, -2.6901406629162469E-5, -6.6036230307136727E-5,
      -9.2708298788542431E-5, -0.00010232959056507142, -9.6579831848347581E-5,
      -8.5166461906840892E-5, -7.43629120407087E-5, -5.4471158193740883E-5,
      -4.0337091180693357E-5, -2.678659607847696E-5, -1.3293835912164994E-5,
      6.222474671702698E-7, 4.76453611777216E-6, 6.7159047249636966E-6,
      7.7286845418531044E-6, 1.1304869419819071E-5, 5.7704299424956009E-6,
      9.3987852254681252E-6, 3.0080823201878794E-6, 7.2579127710765907E-6,
      -2.2833976279696969E-6, -2.4165564877120423E-6, -1.9221954836320465E-6,
      -5.4125017321690375E-7, 5.3338914785319042E-7, -2.1473632654384222E-6,
      1.5612801770181021E-6, 1.1447302385216893E-6, 8.9066128424165655E-7,
      -2.0190289892085468E-6, 5.6736455309646943E-6, 1.5753534406813383E-6,
      1.0045095878134507E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.2863580534297363, 0.30388712157321351, 0.32058719854400353,
      0.33585079512350846, 0.34892928333846235, 0.35890710080610477,
      0.36459861210365896, 0.3646017504531408, 0.35715747482894045,
      0.3401494649987204, 0.31099307158098377, 0.26656684946740572,
      0.20309918629527493, 0.11605929055481011, -6.8114600179122071E-7,
      3.605002344735508E-7, 9.3503694682365264E-7, -4.4925878334433644E-6,
      5.7411343587686031E-6, 3.0127660095857174E-7, -4.1603537999238815E-6,
      2.4804454047137768E-6, 2.482012470073892E-6, -4.1264432681142451E-6,
      4.7999731904128364E-6, -9.588422770588874E-7, 4.4229817670477221E-6,
      3.6865786261663011E-6, -8.0564205059786352E-7, -4.25765447079195E-6,
      -2.6510577663122987E-6, -3.1946907413640635E-6, -2.7130947804825975E-6,
      -7.5545678226183275E-7, -1.6311959772990906E-6, 4.7507185877008426E-6,
      4.8893525545105438E-6, 3.8934139997939938E-6, 4.2342564056477782E-6,
      4.5592851431061253E-6, -4.8108877809421337E-6, 1.0196206264738351E-6,
      4.6899021147630865E-6, -3.3880366279748735E-6, 3.6153089999916558E-6,
      2.0022781755501559E-6, -1.7831184175637092E-6, 3.0702539510504624E-6,
      8.74287476146361E-7, 8.2186612200281559E-7, 5.39590501843099E-6,
      -3.631391777688574E-6, 6.6919991059851045E-6, 4.8380742460294618E-6,
      5.818165585840308E-6, -4.242993642644755E-6, -3.6240504482013452E-6,
      -4.9969357926486441E-7, -4.5360546240050384E-6, 5.2845701254707074E-6,
      1.8471184335598747E-6, 4.3080070518112546E-6, 9.5225610763084631E-7,
      -1.1280176091291178E-6, 2.5397930577713676E-7, -1.2105281630758667E-6,
      1.651420436456538E-6, 9.8948993533147875E-7, -8.4871406637329E-7,
      6.0406259073534964E-7, -9.7622635598292336E-7, -6.4839412236793732E-7,
      2.7093176903993651E-6, 3.9051957185052697E-7, 5.8737928280345482E-6,
      -1.1679144079501365E-7, -2.0316449380111113E-8, 3.6735205478780023E-6,
      2.1918899556798043E-6, 2.1379863057202913E-6, 3.4579353806520929E-6,
      5.3095577011756324E-7, 1.3123833523591946E-6, -2.2914297174499277E-8,
      -6.7175015772480345E-7, -1.8089972211045393E-6, 4.2935158887455759E-6,
      -2.5871493471697104E-6, -2.901594395040074E-6, -2.210398429933073E-6,
      9.1942642588522542E-7, 5.812383894507348E-6, -4.8278917973093362E-7,
      1.9944331394003933E-6, 3.6866034008942648E-6, -3.2726608616084918E-6,
      -2.4334828839173557E-6, -2.8029268903446592E-6, -5.3536469291195208E-6,
      1.0045095878134507E-6, 1.0045095878134507E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    part4_heli_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    part4_heli_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    part4_heli_DW.FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    char fileName[509] = "pitch_data.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(part4_heli_M, "Error creating .mat file pitch_data.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,3,0,"pitch_data")) {
      rtmSetErrorStatus(part4_heli_M,
                        "Error writing mat file header to file pitch_data.mat");
      return;
    }

    part4_heli_DW.ToFile_IWORK.Count = 0;
    part4_heli_DW.ToFile_IWORK.Decimation = -1;
    part4_heli_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File1' */
  {
    char fileName[509] = "scope_data.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(part4_heli_M, "Error creating .mat file scope_data.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,7,0,"scope_data")) {
      rtmSetErrorStatus(part4_heli_M,
                        "Error writing mat file header to file scope_data.mat");
      return;
    }

    part4_heli_DW.ToFile1_IWORK.Count = 0;
    part4_heli_DW.ToFile1_IWORK.Decimation = -1;
    part4_heli_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File2' */
  {
    char fileName[509] = "elev_data.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(part4_heli_M, "Error creating .mat file elev_data.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,3,0,"elev_data")) {
      rtmSetErrorStatus(part4_heli_M,
                        "Error writing mat file header to file elev_data.mat");
      return;
    }

    part4_heli_DW.ToFile2_IWORK.Count = 0;
    part4_heli_DW.ToFile2_IWORK.Decimation = -1;
    part4_heli_DW.ToFile2_PWORK.FilePtr = fp;
  }

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  part4_heli_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  part4_heli_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  part4_heli_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  part4_heli_X.Integrator_CSTATE = part4_heli_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  part4_heli_DW.TimeStampA = (rtInf);
  part4_heli_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void part4_heli_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: part4_heli/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(part4_heli_DW.HILInitialize_Card);
    hil_monitor_stop_all(part4_heli_DW.HILInitialize_Card);
    is_switching = false;
    if ((part4_heli_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (part4_heli_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &part4_heli_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = part4_heli_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((part4_heli_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (part4_heli_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &part4_heli_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = part4_heli_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(part4_heli_DW.HILInitialize_Card
                         , part4_heli_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , part4_heli_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &part4_heli_DW.HILInitialize_AOVoltages[0]
                         , &part4_heli_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(part4_heli_DW.HILInitialize_Card,
            part4_heli_P.HILInitialize_analog_output_cha,
            num_final_analog_outputs, &part4_heli_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(part4_heli_DW.HILInitialize_Card,
            part4_heli_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &part4_heli_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(part4_heli_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(part4_heli_DW.HILInitialize_Card);
    hil_monitor_delete_all(part4_heli_DW.HILInitialize_Card);
    hil_close(part4_heli_DW.HILInitialize_Card);
    part4_heli_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) part4_heli_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "pitch_data.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(part4_heli_M, "Error closing MAT-file pitch_data.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(part4_heli_M,
                          "Error reopening MAT-file pitch_data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 3, part4_heli_DW.ToFile_IWORK.Count,
           "pitch_data")) {
        rtmSetErrorStatus(part4_heli_M,
                          "Error writing header for pitch_data to MAT-file pitch_data.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(part4_heli_M, "Error closing MAT-file pitch_data.mat");
        return;
      }

      part4_heli_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) part4_heli_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "scope_data.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(part4_heli_M, "Error closing MAT-file scope_data.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(part4_heli_M,
                          "Error reopening MAT-file scope_data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 7, part4_heli_DW.ToFile1_IWORK.Count,
           "scope_data")) {
        rtmSetErrorStatus(part4_heli_M,
                          "Error writing header for scope_data to MAT-file scope_data.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(part4_heli_M, "Error closing MAT-file scope_data.mat");
        return;
      }

      part4_heli_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File2' */
  {
    FILE *fp = (FILE *) part4_heli_DW.ToFile2_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "elev_data.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(part4_heli_M, "Error closing MAT-file elev_data.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(part4_heli_M, "Error reopening MAT-file elev_data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 3, part4_heli_DW.ToFile2_IWORK.Count,
           "elev_data")) {
        rtmSetErrorStatus(part4_heli_M,
                          "Error writing header for elev_data to MAT-file elev_data.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(part4_heli_M, "Error closing MAT-file elev_data.mat");
        return;
      }

      part4_heli_DW.ToFile2_PWORK.FilePtr = (NULL);
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
  part4_heli_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  part4_heli_update();
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
  part4_heli_initialize();
}

void MdlTerminate(void)
{
  part4_heli_terminate();
}

/* Registration function */
RT_MODEL_part4_heli_T *part4_heli(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  part4_heli_P.Integrator_UpperSat = rtInf;
  part4_heli_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)part4_heli_M, 0,
                sizeof(RT_MODEL_part4_heli_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&part4_heli_M->solverInfo,
                          &part4_heli_M->Timing.simTimeStep);
    rtsiSetTPtr(&part4_heli_M->solverInfo, &rtmGetTPtr(part4_heli_M));
    rtsiSetStepSizePtr(&part4_heli_M->solverInfo,
                       &part4_heli_M->Timing.stepSize0);
    rtsiSetdXPtr(&part4_heli_M->solverInfo, &part4_heli_M->ModelData.derivs);
    rtsiSetContStatesPtr(&part4_heli_M->solverInfo, (real_T **)
                         &part4_heli_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&part4_heli_M->solverInfo,
      &part4_heli_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&part4_heli_M->solverInfo, (&rtmGetErrorStatus
      (part4_heli_M)));
    rtsiSetRTModelPtr(&part4_heli_M->solverInfo, part4_heli_M);
  }

  rtsiSetSimTimeStep(&part4_heli_M->solverInfo, MAJOR_TIME_STEP);
  part4_heli_M->ModelData.intgData.f[0] = part4_heli_M->ModelData.odeF[0];
  part4_heli_M->ModelData.contStates = ((real_T *) &part4_heli_X);
  rtsiSetSolverData(&part4_heli_M->solverInfo, (void *)
                    &part4_heli_M->ModelData.intgData);
  rtsiSetSolverName(&part4_heli_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = part4_heli_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    part4_heli_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    part4_heli_M->Timing.sampleTimes = (&part4_heli_M->Timing.sampleTimesArray[0]);
    part4_heli_M->Timing.offsetTimes = (&part4_heli_M->Timing.offsetTimesArray[0]);

    /* task periods */
    part4_heli_M->Timing.sampleTimes[0] = (0.0);
    part4_heli_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    part4_heli_M->Timing.offsetTimes[0] = (0.0);
    part4_heli_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(part4_heli_M, &part4_heli_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = part4_heli_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    part4_heli_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(part4_heli_M, -1);
  part4_heli_M->Timing.stepSize0 = 0.002;
  part4_heli_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  part4_heli_M->Sizes.checksums[0] = (3648677838U);
  part4_heli_M->Sizes.checksums[1] = (2711651165U);
  part4_heli_M->Sizes.checksums[2] = (1139160593U);
  part4_heli_M->Sizes.checksums[3] = (2034937542U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    part4_heli_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(part4_heli_M->extModeInfo,
      &part4_heli_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(part4_heli_M->extModeInfo, part4_heli_M->Sizes.checksums);
    rteiSetTPtr(part4_heli_M->extModeInfo, rtmGetTPtr(part4_heli_M));
  }

  part4_heli_M->solverInfoPtr = (&part4_heli_M->solverInfo);
  part4_heli_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&part4_heli_M->solverInfo, 0.002);
  rtsiSetSolverMode(&part4_heli_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  part4_heli_M->ModelData.blockIO = ((void *) &part4_heli_B);

  {
    int_T i;
    for (i = 0; i < 6; i++) {
      part4_heli_B.Gain1[i] = 0.0;
    }

    part4_heli_B.TravelCounttorad = 0.0;
    part4_heli_B.Gain = 0.0;
    part4_heli_B.Sum3 = 0.0;
    part4_heli_B.Gain_d = 0.0;
    part4_heli_B.PitchCounttorad = 0.0;
    part4_heli_B.Gain_i = 0.0;
    part4_heli_B.Gain_b = 0.0;
    part4_heli_B.ElevationCounttorad = 0.0;
    part4_heli_B.Gain_e = 0.0;
    part4_heli_B.Sum = 0.0;
    part4_heli_B.Gain_dg = 0.0;
    part4_heli_B.Sum1[0] = 0.0;
    part4_heli_B.Sum1[1] = 0.0;
    part4_heli_B.Vd_bias = 0.0;
    part4_heli_B.Sum1_c = 0.0;
    part4_heli_B.Vs_bias = 0.0;
    part4_heli_B.Sum2 = 0.0;
    part4_heli_B.K_ei = 0.0;
    part4_heli_B.Gain_l = 0.0;
    part4_heli_B.BackmotorSaturation = 0.0;
    part4_heli_B.FrontmotorSaturation = 0.0;
  }

  /* parameters */
  part4_heli_M->ModelData.defaultParam = ((real_T *)&part4_heli_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &part4_heli_X;
    part4_heli_M->ModelData.contStates = (x);
    (void) memset((void *)&part4_heli_X, 0,
                  sizeof(X_part4_heli_T));
  }

  /* states (dwork) */
  part4_heli_M->ModelData.dwork = ((void *) &part4_heli_DW);
  (void) memset((void *)&part4_heli_DW, 0,
                sizeof(DW_part4_heli_T));

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      part4_heli_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      part4_heli_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      part4_heli_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      part4_heli_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      part4_heli_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      part4_heli_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      part4_heli_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      part4_heli_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  part4_heli_DW.TimeStampA = 0.0;
  part4_heli_DW.LastUAtTimeA = 0.0;
  part4_heli_DW.TimeStampB = 0.0;
  part4_heli_DW.LastUAtTimeB = 0.0;
  part4_heli_DW.HILWriteAnalog_Buffer[0] = 0.0;
  part4_heli_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    part4_heli_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  part4_heli_M->Sizes.numContStates = (4);/* Number of continuous states */
  part4_heli_M->Sizes.numY = (0);      /* Number of model outputs */
  part4_heli_M->Sizes.numU = (0);      /* Number of model inputs */
  part4_heli_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  part4_heli_M->Sizes.numSampTimes = (2);/* Number of sample times */
  part4_heli_M->Sizes.numBlocks = (71);/* Number of blocks */
  part4_heli_M->Sizes.numBlockIO = (21);/* Number of block outputs */
  part4_heli_M->Sizes.numBlockPrms = (153);/* Sum of parameter "widths" */
  return part4_heli_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
