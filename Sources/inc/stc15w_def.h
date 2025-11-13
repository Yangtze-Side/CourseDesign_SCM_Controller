#ifndef __STC15W_DEF_H__
#define __STC15W_DEF_H__

/////////////////////////////////////////////////

#include "stc15.h"
#include "def.h"

/////////////////////////////////////////////////

#define PORT_SetInitLevelLow(p, b)      CLR_REG_BIT(P##p, (b))
#define PORT_SetInitLevelHigh(p, b)     SET_REG_BIT(P##p, (b))

#define PORT_SetQuasiMode(p, b)         CLR_REG_BIT(P##p##M0, (b)); \
                                        CLR_REG_BIT(P##p##M1, (b))

#define PORT_SetPushPullMode(p, b)      SET_REG_BIT(P##p##M0, (b)); \
                                        CLR_REG_BIT(P##p##M1, (b))

#define PORT_SetHighZInputMode(p, b)    CLR_REG_BIT(P##p##M0, (b)); \
                                        SET_REG_BIT(P##p##M1, (b))

#define PORT_SetOpenDrainMode(p, b)     SET_REG_BIT(P##p##M0, (b)); \
                                        SET_REG_BIT(P##p##M1, (b))

#define PORT_SetAnalogInput(p, b)       SET_REG_BIT(P##p##ASF, (b))
#define PORT_SetDigitalInput(p, b)      CLR_REG_BIT(P##p##ASF, (b))

#define SetP0nInitLevelLow(b)           PORT_SetInitLevelLow(0, (b))
#define SetP1nInitLevelLow(b)           PORT_SetInitLevelLow(1, (b))
#define SetP2nInitLevelLow(b)           PORT_SetInitLevelLow(2, (b))
#define SetP3nInitLevelLow(b)           PORT_SetInitLevelLow(3, (b))
#define SetP4nInitLevelLow(b)           PORT_SetInitLevelLow(4, (b))
#define SetP5nInitLevelLow(b)           PORT_SetInitLevelLow(5, (b))
#define SetP6nInitLevelLow(b)           PORT_SetInitLevelLow(6, (b))
#define SetP7nInitLevelLow(b)           PORT_SetInitLevelLow(7, (b))

#define SetP0nInitLevelHigh(b)          PORT_SetInitLevelHigh(0, (b))
#define SetP1nInitLevelHigh(b)          PORT_SetInitLevelHigh(1, (b))
#define SetP2nInitLevelHigh(b)          PORT_SetInitLevelHigh(2, (b))
#define SetP3nInitLevelHigh(b)          PORT_SetInitLevelHigh(3, (b))
#define SetP4nInitLevelHigh(b)          PORT_SetInitLevelHigh(4, (b))
#define SetP5nInitLevelHigh(b)          PORT_SetInitLevelHigh(5, (b))
#define SetP6nInitLevelHigh(b)          PORT_SetInitLevelHigh(6, (b))
#define SetP7nInitLevelHigh(b)          PORT_SetInitLevelHigh(7, (b))

#define SetP0nQuasiMode(b)              PORT_SetQuasiMode(0, (b))
#define SetP1nQuasiMode(b)              PORT_SetQuasiMode(1, (b))
#define SetP2nQuasiMode(b)              PORT_SetQuasiMode(2, (b))
#define SetP3nQuasiMode(b)              PORT_SetQuasiMode(3, (b))
#define SetP4nQuasiMode(b)              PORT_SetQuasiMode(4, (b))
#define SetP5nQuasiMode(b)              PORT_SetQuasiMode(5, (b))
#define SetP6nQuasiMode(b)              PORT_SetQuasiMode(6, (b))
#define SetP7nQuasiMode(b)              PORT_SetQuasiMode(7, (b))

#define SetP0nPushPullMode(b)           PORT_SetPushPullMode(0, (b))
#define SetP1nPushPullMode(b)           PORT_SetPushPullMode(1, (b))
#define SetP2nPushPullMode(b)           PORT_SetPushPullMode(2, (b))
#define SetP3nPushPullMode(b)           PORT_SetPushPullMode(3, (b))
#define SetP4nPushPullMode(b)           PORT_SetPushPullMode(4, (b))
#define SetP5nPushPullMode(b)           PORT_SetPushPullMode(5, (b))
#define SetP6nPushPullMode(b)           PORT_SetPushPullMode(6, (b))
#define SetP7nPushPullMode(b)           PORT_SetPushPullMode(7, (b))

#define SetP0nHighZInputMode(b)         PORT_SetHighZInputMode(0, (b))
#define SetP1nHighZInputMode(b)         PORT_SetHighZInputMode(1, (b))
#define SetP2nHighZInputMode(b)         PORT_SetHighZInputMode(2, (b))
#define SetP3nHighZInputMode(b)         PORT_SetHighZInputMode(3, (b))
#define SetP4nHighZInputMode(b)         PORT_SetHighZInputMode(4, (b))
#define SetP5nHighZInputMode(b)         PORT_SetHighZInputMode(5, (b))
#define SetP6nHighZInputMode(b)         PORT_SetHighZInputMode(6, (b))
#define SetP7nHighZInputMode(b)         PORT_SetHighZInputMode(7, (b))

#define SetP0nOpenDrainMode(b)          PORT_SetOpenDrainMode(0, (b))
#define SetP1nOpenDrainMode(b)          PORT_SetOpenDrainMode(1, (b))
#define SetP2nOpenDrainMode(b)          PORT_SetOpenDrainMode(2, (b))
#define SetP3nOpenDrainMode(b)          PORT_SetOpenDrainMode(3, (b))
#define SetP4nOpenDrainMode(b)          PORT_SetOpenDrainMode(4, (b))
#define SetP5nOpenDrainMode(b)          PORT_SetOpenDrainMode(5, (b))
#define SetP6nOpenDrainMode(b)          PORT_SetOpenDrainMode(6, (b))
#define SetP7nOpenDrainMode(b)          PORT_SetOpenDrainMode(7, (b))

#define SetP1nAnalogInput(b)            PORT_SetAnalogInput(1, (b))
#define SetP1nDigitalInput(b)           PORT_SetDigitalInput(1, (b))

/////////////////////////////////////////////////

#define EnableGlobalInt()               (EA = 1)
#define DisableGlobalInt()              (EA = 0)

#define INT0_EnableInt()                (EX0 = 1)
#define INT0_DisableInt()               (EX0 = 0)

#define INT1_EnableInt()                (EX1 = 1)
#define INT1_DisableInt()               (EX1 = 0)

#define INTCLKO_EX2_MSK                 BIT4
#define INT2_EnableInt()                SET_REG_BIT(INT_CLKO, INTCLKO_EX2_MSK)
#define INT2_DisableInt()               CLR_REG_BIT(INT_CLKO, INTCLKO_EX2_MSK)

#define INTCLKO_EX3_MSK                 BIT5
#define INT3_EnableInt()                SET_REG_BIT(INT_CLKO, INTCLKO_EX3_MSK)
#define INT3_DisableInt()               CLR_REG_BIT(INT_CLKO, INTCLKO_EX3_MSK)

#define INTCLKO_EX4_MSK                 BIT6
#define INT4_EnableInt()                SET_REG_BIT(INT_CLKO, INTCLKO_EX4_MSK)
#define INT4_DisableInt()               CLR_REG_BIT(INT_CLKO, INTCLKO_EX4_MSK)

#define TIMER0_EnableInt()              (ET0 = 1)
#define TIMER0_DisableInt()             (ET0 = 0)

#define TIMER1_EnableInt()              (ET1 = 1)
#define TIMER1_DisableInt()             (ET1 = 0)

#define IE2_ET2_MSK                     BIT2
#define TIMER2_EnableInt()              SET_REG_BIT(IE2, IE2_ET2_MSK)
#define TIMER2_DisableInt()             CLR_REG_BIT(IE2, IE2_ET2_MSK)

#define IE2_ET3_MSK                     BIT5
#define TIMER3_EnableInt()              SET_REG_BIT(IE2, IE2_ET3_MSK)
#define TIMER3_DisableInt()             CLR_REG_BIT(IE2, IE2_ET3_MSK)

#define IE2_ET4_MSK                     BIT6
#define TIMER4_EnableInt()              SET_REG_BIT(IE2, IE2_ET4_MSK)
#define TIMER4_DisableInt()             CLR_REG_BIT(IE2, IE2_ET4_MSK)

#define UART1_EnableInt()               (ES = 1)
#define UART1_DisableInt()              (ES = 0)

#define IE2_ES2_MSK                     BIT0
#define UART2_EnableInt()               SET_REG_BIT(IE2, IE2_ES2_MSK)
#define UART2_DisableInt()              CLR_REG_BIT(IE2, IE2_ES2_MSK)

#define IE2_ES3_MSK                     BIT3
#define UART3_EnableInt()               SET_REG_BIT(IE2, IE2_ES3_MSK)
#define UART3_DisableInt()              CLR_REG_BIT(IE2, IE2_ES3_MSK)

#define IE2_ES4_MSK                     BIT4
#define UART4_EnableInt()               SET_REG_BIT(IE2, IE2_ES4_MSK)
#define UART4_DisableInt()              CLR_REG_BIT(IE2, IE2_ES4_MSK)

#define LVD_EnableInt()                 (ELVD = 1)
#define LVD_DisableInt()                (ELVD = 0)

#define ADC_EnableInt()                 (EADC = 1)
#define ADC_DisableInt()                (EADC = 0)

#define IE2_ESPI_MSK                    BIT1
#define SPI_EnableInt()                 SET_REG_BIT(IE2, IE2_ESPI_MSK)
#define SPI_DisableInt()                CLR_REG_BIT(IE2, IE2_ESPI_MSK)

#define CMPCR1_PIE_MSK                  BIT5
#define CMPCR1_NIE_MSK                  BIT4
#define CMP_EnablePosedgeInt()          SET_REG_BIT(CMPCR1, CMPCR1_PIE_MSK)
#define CMP_EnableNegedgeInt()          SET_REG_BIT(CMPCR1, CMPCR1_NIE_MSK)
#define CMP_EnableEdgeInt()             SET_REG_BIT(CMPCR1, (CMPCR1_PIE_MSK | CMPCR1_NIE_MSK))
#define CMP_DisableInt()                CLR_REG_BIT(CMPCR1, (CMPCR1_PIE_MSK | CMPCR1_NIE_MSK))

#define PWMFDCR_EFDI_MSK                BIT3
#define PWMFD_EnableInt()               SET_REG_BIT(PWMFDCR, PWMFDCR_EFDI_MSK)
#define PWMFD_DisableInt()              CLR_REG_BIT(PWMFDCR, PWMFDCR_EFDI_MSK)

#define PWMCR_ECBI_MSK                  BIT6
#define PWM_EnableCounterInt()          SET_REG_BIT(PWMCR, PWMCR_ECBI_MSK)
#define PWM_DisableCounterInt()         CLR_REG_BIT(PWMCR, PWMCR_ECBI_MSK)

#define PWMnCR_EPWMI_MSK                BIT2
#define PWMnCR_ET2I_MSK                 BIT1
#define PWMnCR_ET1I_MSK                 BIT0
#define PWM_EnableCnT1Int(n)            SET_REG_BIT(PWM##n##CR, (PWMnCR_EPWMI_MSK | PWMnCR_ET1I_MSK))
#define PWM_EnableCnT2Int(n)            SET_REG_BIT(PWM##n##CR, (PWMnCR_EPWMI_MSK | PWMnCR_ET2I_MSK))
#define PWM_EnableCnT1T2Int(n)          SET_REG_BIT(PWM##n##CR, (PWMnCR_EPWMI_MSK | PWMnCR_ET1I_MSK | PWMnCR_ET2I_MSK))
#define PWM_DisableCnInt(n)             CLR_REG_BIT(PWM##n##CR, PWMnCR_EPWMI_MSK)

#define PWM_EnableC2T1Int()             PWM_EnableCnT1Int(2)
#define PWM_EnableC3T1Int()             PWM_EnableCnT1Int(3)
#define PWM_EnableC4T1Int()             PWM_EnableCnT1Int(4)
#define PWM_EnableC5T1Int()             PWM_EnableCnT1Int(5)
#define PWM_EnableC6T1Int()             PWM_EnableCnT1Int(6)
#define PWM_EnableC7T1Int()             PWM_EnableCnT1Int(7)

#define PWM_EnableC2T2Int()             PWM_EnableCnT2Int(2)
#define PWM_EnableC3T2Int()             PWM_EnableCnT2Int(3)
#define PWM_EnableC4T2Int()             PWM_EnableCnT2Int(4)
#define PWM_EnableC5T2Int()             PWM_EnableCnT2Int(5)
#define PWM_EnableC6T2Int()             PWM_EnableCnT2Int(6)
#define PWM_EnableC7T2Int()             PWM_EnableCnT2Int(7)

#define PWM_EnableC2T1T2Int()           PWM_EnableCnT1T2Int(2)
#define PWM_EnableC3T1T2Int()           PWM_EnableCnT1T2Int(3)
#define PWM_EnableC4T1T2Int()           PWM_EnableCnT1T2Int(4)
#define PWM_EnableC5T1T2Int()           PWM_EnableCnT1T2Int(5)
#define PWM_EnableC6T1T2Int()           PWM_EnableCnT1T2Int(6)
#define PWM_EnableC7T1T2Int()           PWM_EnableCnT1T2Int(7)

#define PWM_DisableC2Int()              PWM_DisableCnInt(2)
#define PWM_DisableC3Int()              PWM_DisableCnInt(3)
#define PWM_DisableC4Int()              PWM_DisableCnInt(4)
#define PWM_DisableC5Int()              PWM_DisableCnInt(5)
#define PWM_DisableC6Int()              PWM_DisableCnInt(6)
#define PWM_DisableC7Int()              PWM_DisableCnInt(7)

#define CMOD_ECF_MSK                    BIT0
#define PCA_EnableCounterInt()          SET_REG_BIT(CMOD, CMOD_ECF_MSK)
#define PCA_DisableCounterInt()         CLR_REG_BIT(CMOD, CMOD_ECF_MSK)

#define CCAPM0_ECCF0_MSK                BIT0
#define CCAPM1_ECCF1_MSK                BIT0
#define PCA_EnableCCF0Int()             SET_REG_BIT(CCAPM0, CCAPM0_ECCF0_MSK)
#define PCA_EnableCCF1Int()             SET_REG_BIT(CCAPM1, CCAPM1_ECCF1_MSK)
#define PCA_DisableCCF0Int()            CLR_REG_BIT(CCAPM0, CCAPM0_ECCF0_MSK)
#define PCA_DisableCCF1Int()            CLR_REG_BIT(CCAPM1, CCAPM1_ECCF1_MSK)

#define INT0_FallingRisingInt()         (IT0 = 0)
#define INT0_FallingInt()               (IT0 = 1)

#define INT0_CheckFlag()                (IE0)
#define INT0_ClearFlag()                (IE0 = 0)

#define INT1_FallingRisingInt()         (IT1 = 0)
#define INT1_FallingInt()               (IT1 = 1)

#define INT1_CheckFlag()                (IE1)
#define INT1_ClearFlag()                (IE1 = 0)

#define TIMER0_CheckFlag()              (TF0)
#define TIMER0_ClearFlag()              (TF0 = 0)

#define TIMER1_CheckFlag()              (TF1)
#define TIMER1_ClearFlag()              (TF1 = 0)

#define UART1_CheckRxFlag()             (RI)
#define UART1_CheckTxFlag()             (TI)
#define UART1_ClearRxFlag()             (RI = 0)
#define UART1_ClearTxFlag()             (TI = 0)
#define UART1_SetRxFlag()               (RI = 1)
#define UART1_SetTxFlag()               (TI = 1)

#define S2CON_S2TI_MSK                  BIT1
#define S2CON_S2RI_MSK                  BIT0
#define UART2_CheckRxFlag()             READ_REG_BIT(S2CON, S2CON_S2RI_MSK)
#define UART2_CheckTxFlag()             READ_REG_BIT(S2CON, S2CON_S2TI_MSK)
#define UART2_ClearRxFlag()             CLR_REG_BIT(S2CON, S2CON_S2RI_MSK)
#define UART2_ClearTxFlag()             CLR_REG_BIT(S2CON, S2CON_S2TI_MSK)
#define UART2_SetRxFlag()               SET_REG_BIT(S2CON, S2CON_S2RI_MSK)
#define UART2_SetTxFlag()               SET_REG_BIT(S2CON, S2CON_S2TI_MSK)

#define S3CON_S3TI_MSK                  BIT1
#define S3CON_S3RI_MSK                  BIT0
#define UART3_CheckRxFlag()             READ_REG_BIT(S3CON, S3CON_S3RI_MSK)
#define UART3_CheckTxFlag()             READ_REG_BIT(S3CON, S3CON_S3TI_MSK)
#define UART3_ClearRxFlag()             CLR_REG_BIT(S3CON, S3CON_S3RI_MSK)
#define UART3_ClearTxFlag()             CLR_REG_BIT(S3CON, S3CON_S3TI_MSK)
#define UART3_SetRxFlag()               SET_REG_BIT(S3CON, S3CON_S3RI_MSK)
#define UART3_SetTxFlag()               SET_REG_BIT(S3CON, S3CON_S3TI_MSK)

#define S4CON_S4TI_MSK                  BIT1
#define S4CON_S4RI_MSK                  BIT0
#define UART4_CheckRxFlag()             READ_REG_BIT(S4CON, S4CON_S4RI_MSK)
#define UART4_CheckTxFlag()             READ_REG_BIT(S4CON, S4CON_S4TI_MSK)
#define UART4_ClearRxFlag()             CLR_REG_BIT(S4CON, S4CON_S4RI_MSK)
#define UART4_ClearTxFlag()             CLR_REG_BIT(S4CON, S4CON_S4TI_MSK)
#define UART4_SetRxFlag()               SET_REG_BIT(S4CON, S4CON_S4RI_MSK)
#define UART4_SetTxFlag()               SET_REG_BIT(S4CON, S4CON_S4TI_MSK)

#define PCON_LVDF_MSK                   BIT5
#define LVD_CheckFlag()                 READ_REG_BIT(PCON, PCON_LVDF_MSK)
#define LVD_ClearFlag()                 CLR_REG_BIT(PCON, PCON_LVDF_MSK)

#define ADCCONTR_ADCFLAG_MSK            BIT4
#define ADC_CheckFlag()                 READ_REG_BIT(ADC_CONTR, ADCCONTR_ADCFLAG_MSK)
#define ADC_ClearFlag()                 CLR_REG_BIT(ADC_CONTR, ADCCONTR_ADCFLAG_MSK)

#define SPSTAT_SPIF_MSK                 BIT7
#define SPSTAT_WCOL_MSK                 BIT6
#define SPI_CheckFlag()                 READ_REG_BIT(SPSTAT, SPSTAT_SPIF_MSK)
#define SPI_ClearFlag()                 SET_REG_BIT(SPSTAT, SPSTAT_SPIF_MSK | SPSTAT_WCOL_MSK)

#define CMPCR1_CMPIF_MSK                BIT6
#define CMP_CheckFlag()                 READ_REG_BIT(CMPCR1, CMPCR1_CMPIF_MSK)
#define CMP_ClearFlag()                 CLR_REG_BIT(CMPCR1, CMPCR1_CMPIF_MSK)

#define PWMFDCR_FDIF_MSK                BIT0
#define PWMFD_CheckFlag()               READ_REG_BIT(PWMFDCR, PWMFDCR_FDIF_MSK)
#define PWMFD_ClearFlag()               CLR_REG_BIT(PWMFDCR, PWMFDCR_FDIF_MSK)

#define PWMIF_CBIF_MSK                  BIT6
#define PWM_CheckCounterFlag()          READ_REG_BIT(PWMIF, PWMIF_CBIF_MSK)
#define PWM_ClearCounterFlag()          CLR_REG_BIT(PWMIF, PWMIF_CBIF_MSK)

#define PWMIF_C2IF_MSK                  BIT0
#define PWMIF_C3IF_MSK                  BIT1
#define PWMIF_C4IF_MSK                  BIT2
#define PWMIF_C5IF_MSK                  BIT3
#define PWMIF_C6IF_MSK                  BIT4
#define PWMIF_C7IF_MSK                  BIT5
#define PWM_CheckC2Flag()               READ_REG_BIT(PWMIF, PWMIF_C2IF_MSK)
#define PWM_CheckC3Flag()               READ_REG_BIT(PWMIF, PWMIF_C3IF_MSK)
#define PWM_CheckC4Flag()               READ_REG_BIT(PWMIF, PWMIF_C4IF_MSK)
#define PWM_CheckC5Flag()               READ_REG_BIT(PWMIF, PWMIF_C5IF_MSK)
#define PWM_CheckC6Flag()               READ_REG_BIT(PWMIF, PWMIF_C6IF_MSK)
#define PWM_CheckC7Flag()               READ_REG_BIT(PWMIF, PWMIF_C7IF_MSK)
#define PWM_ClearC2Flag()               CLR_REG_BIT(PWMIF, PWMIF_C2IF_MSK)
#define PWM_ClearC3Flag()               CLR_REG_BIT(PWMIF, PWMIF_C3IF_MSK)
#define PWM_ClearC4Flag()               CLR_REG_BIT(PWMIF, PWMIF_C4IF_MSK)
#define PWM_ClearC5Flag()               CLR_REG_BIT(PWMIF, PWMIF_C5IF_MSK)
#define PWM_ClearC6Flag()               CLR_REG_BIT(PWMIF, PWMIF_C6IF_MSK)
#define PWM_ClearC7Flag()               CLR_REG_BIT(PWMIF, PWMIF_C7IF_MSK)

#define CCON_CF_MSK                     BIT7
#define PCA_CheckCounterFlag()          READ_REG_BIT(CCON, CCON_CF_MSK)
#define PCA_ClearCounterFlag()          CLR_REG_BIT(CCON, CCON_CF_MSK)

#define CCON_CCF0_MSK                   BIT0
#define CCON_CCF1_MSK                   BIT1
#define PCA_CheckCCF0Flag()             READ_REG_BIT(CCON, CCON_CCF0_MSK)
#define PCA_CheckCCF1Flag()             READ_REG_BIT(CCON, CCON_CCF1_MSK)
#define PCA_ClearCCF0Flag()             CLR_REG_BIT(CCON, CCON_CCF0_MSK)
#define PCA_ClearCCF1Flag()             CLR_REG_BIT(CCON, CCON_CCF1_MSK)

#define INT0_SetIntPriority(n)          PX0 = ((n) & 1)

#define INT1_SetIntPriority(n)          PX1 = ((n) & 1)

#define IP2_PX4_MSK                     BIT4
#define INT4_SetIntPriority(n)          MODIFY_REG(IP2, IP2_PX4_MSK, (((n) & 1) << 4))

#define TIMER0_SetIntPriority(n)        PT0 = ((n) & 1)

#define TIMER1_SetIntPriority(n)        PT1 = ((n) & 1)

#define UART1_SetIntPriority(n)         PS = ((n) & 1)

#define IP2_PS2_MSK                     BIT0
#define UART2_SetIntPriority(n)         MODIFY_REG(IP2, IP2_PS2_MSK, (((n) & 1) << 0))

#define LVD_SetIntPriority(n)           PLVD = ((n) & 1)

#define ADC_SetIntPriority(n)           PADC = ((n) & 1)

#define IP2_PSPI_MSK                    BIT1
#define SPI_SetIntPriority(n)           MODIFY_REG(IP2, IP2_PSPI_MSK, (((n) & 1) << 1))

#define IP2_PPWMFD_MSK                  BIT3
#define PWMFD_SetIntPriority(n)         MODIFY_REG(IP2, IP2_PPWMFD_MSK, (((n) & 1) << 3))

#define IP2_PPWM_MSK                    BIT2
#define PWM_SetIntPriority(n)           MODIFY_REG(IP2, IP2_PPWM_MSK, (((n) & 1) << 2))

#define PCA_SetIntPriority(n)           PPCA = ((n) & 1)

/////////////////////////////////////////////////

#define EAXFR_MSK                       BIT7
#define EnableAccessXFR()               SET_REG_BIT(P_SW2, EAXFR_MSK)

#define UART1_PS_MSK                    (BIT7 | BIT6)
#define UART1_SwitchP3031()             MODIFY_REG(P_SW1, UART1_PS_MSK, ((0) << 6))
#define UART1_SwitchP3637()             MODIFY_REG(P_SW1, UART1_PS_MSK, ((1) << 6))
#define UART1_SwitchP1617()             MODIFY_REG(P_SW1, UART1_PS_MSK, ((2) << 6))

#define UART2_PS_MSK                    (BIT0)
#define UART2_SwitchP1011()             CLR_REG_BIT(P_SW2, UART2_PS_MSK)
#define UART2_SwitchP4647()             SET_REG_BIT(P_SW2, UART2_PS_MSK)

#define UART3_PS_MSK                    (BIT1)
#define UART3_SwitchP0001()             CLR_REG_BIT(P_SW2, UART3_PS_MSK)
#define UART3_SwitchP5051()             SET_REG_BIT(P_SW2, UART3_PS_MSK)

#define UART4_PS_MSK                    (BIT2)
#define UART4_SwitchP0203()             CLR_REG_BIT(P_SW2, UART4_PS_MSK)
#define UART4_SwitchP5253()             SET_REG_BIT(P_SW2, UART4_PS_MSK)

#define SPI_PS_MSK                      (BIT3 | BIT2)
#define SPI_SwitchP1n()                 MODIFY_REG(P_SW1, SPI_PS_MSK, ((0) << 2))
#define SPI_SwitchP2n()                 MODIFY_REG(P_SW1, SPI_PS_MSK, ((1) << 2))
#define SPI_SwitchP4n()                 MODIFY_REG(P_SW1, SPI_PS_MSK, ((2) << 2))

#define CMPNS_MSK                       BIT2
#define CMPN_SwitchVREF()               CLR_REG_BIT(CMPCR1, CMPNS_MSK)
#define CMPN_SwitchP54()                SET_REG_BIT(CMPCR1, CMPNS_MSK)

#define CMPPS_MSK                       BIT3
#define CMPP_SwitchP55()                CLR_REG_BIT(CMPCR1, CMPPS_MSK)
#define CMPP_SwitchADCIN()              SET_REG_BIT(CMPCR1, CMPPS_MSK)

#define CMPO_SwitchP12()

#define MCLKO_PS_MSK                    (BIT3)
#define CLK_SYSCLKO_SwitchP54()         CLR_REG_BIT(CLK_DIV, MCLKO_PS_MSK)
#define CLK_SYSCLKO_SwitchP16()         SET_REG_BIT(CLK_DIV, MCLKO_PS_MSK)

#define PCA_PS_MSK                      (BIT5 | BIT4)
#define PCA_SwitchP1n()                 MODIFY_REG(P_SW1, PCA_PS_MSK, ((0) << 4))
#define PCA_SwitchP3n()                 MODIFY_REG(P_SW1, PCA_PS_MSK, ((1) << 4))
#define PCA_SwitchP2n()                 MODIFY_REG(P_SW1, PCA_PS_MSK, ((2) << 4))

#define PWM_C2PS_MSK                    BIT3
#define PWM_C3PS_MSK                    BIT3
#define PWM_C4PS_MSK                    BIT3
#define PWM_C5PS_MSK                    BIT3
#define PWM_C6PS_MSK                    BIT3
#define PWM_C7PS_MSK                    BIT3
#define PWM_C2_SwitchP37()              CLR_REG_BIT(PWM2CR, PWM_C2PS_MSK)
#define PWM_C2_SwitchP27()              SET_REG_BIT(PWM2CR, PWM_C2PS_MSK)
#define PWM_C3_SwitchP21()              CLR_REG_BIT(PWM3CR, PWM_C3PS_MSK)
#define PWM_C3_SwitchP45()              SET_REG_BIT(PWM3CR, PWM_C3PS_MSK)
#define PWM_C4_SwitchP22()              CLR_REG_BIT(PWM4CR, PWM_C4PS_MSK)
#define PWM_C4_SwitchP44()              SET_REG_BIT(PWM4CR, PWM_C4PS_MSK)
#define PWM_C5_SwitchP23()              CLR_REG_BIT(PWM5CR, PWM_C5PS_MSK)
#define PWM_C5_SwitchP42()              SET_REG_BIT(PWM5CR, PWM_C5PS_MSK)
#define PWM_C6_SwitchP16()              CLR_REG_BIT(PWM6CR, PWM_C6PS_MSK)
#define PWM_C6_SwitchP07()              SET_REG_BIT(PWM6CR, PWM_C6PS_MSK)
#define PWM_C7_SwitchP17()              CLR_REG_BIT(PWM7CR, PWM_C7PS_MSK)
#define PWM_C7_SwitchP06()              SET_REG_BIT(PWM7CR, PWM_C7PS_MSK)

/////////////////////////////////////////////////

#define MCLKODIV_MSK                    (BIT7 | BIT6)
#define MCLKODIV2_MSK                   BIT3
#define CLK_SYSCLKO_Divider(n)          MODIFY_REG(CLK_DIV, MCLKODIV_MSK, ((n) << 6)); \
										MODIFY_REG(INT_CLKO, MCLKODIV2_MSK, (((n) & 4) << 1))
#define CLK_SYSCLKO_Divider1()			CLK_SYSCLKO_Divider(1)
#define CLK_SYSCLKO_Divider2()			CLK_SYSCLKO_Divider(2)
#define CLK_SYSCLKO_Divider4()			CLK_SYSCLKO_Divider(3)
#define CLK_SYSCLKO_Divider16()			CLK_SYSCLKO_Divider(4)

/////////////////////////////////////////////////

#define WDTCONTR_FLAG_MSK               BIT7
#define WDTCONTR_EN_MSK                 BIT5
#define WDTCONTR_CLR_MSK                BIT4
#define WDTCONTR_IDL_MSK                BIT3
#define WDTCONTR_PS_MSK                 (BIT2 | BIT1 | BIT0)

#define WDT_Enable()                    SET_REG_BIT(WDT_CONTR, WDTCONTR_EN_MSK)
#define WDT_Clear()                     SET_REG_BIT(WDT_CONTR, WDTCONTR_CLR_MSK)
#define WDT_CheckWDTReset()             READ_REG_BIT(WDT_CONTR, WDTCONTR_FLAG_MSK)
#define WDT_IdlePause()                 CLR_REG_BIT(WDT_CONTR, WDTCONTR_IDL_MSK)
#define WDT_IdleContinue()              SET_REG_BIT(WDT_CONTR, WDTCONTR_IDL_MSK)

#define WDT_SetPrescale(n)              MODIFY_REG(WDT_CONTR, WDTCONTR_PS_MSK, ((n) << 0))
#define WDT_SetPrescale2()              WDT_SetPrescale(0)
#define WDT_SetPrescale4()              WDT_SetPrescale(1)
#define WDT_SetPrescale8()              WDT_SetPrescale(2)
#define WDT_SetPrescale16()             WDT_SetPrescale(3)
#define WDT_SetPrescale32()             WDT_SetPrescale(4)
#define WDT_SetPrescale64()             WDT_SetPrescale(5)
#define WDT_SetPrescale128()            WDT_SetPrescale(6)
#define WDT_SetPrescale256()            WDT_SetPrescale(7)

/////////////////////////////////////////////////

#define TIMER0_Run()                    (TR0 = 1)
#define TIMER0_Stop()                   (TR0 = 0)

#define TIMER0_SetReload8(n)            (TH0 = LOBYTE(n), TL0 = LOBYTE(n))
#define TIMER0_SetReload16(n)           (TH0 = HIBYTE(n), TL0 = LOBYTE(n))

#define TMOD_T0M_MSK                    (BIT1 | BIT0)
#define TIMER0_Mode0()                  MODIFY_REG(TMOD, TMOD_T0M_MSK, ((0) << 0))
#define TIMER0_Mode1()                  MODIFY_REG(TMOD, TMOD_T0M_MSK, ((1) << 0))
#define TIMER0_Mode2()                  MODIFY_REG(TMOD, TMOD_T0M_MSK, ((2) << 0))
#define TIMER0_Mode3()                  MODIFY_REG(TMOD, TMOD_T0M_MSK, ((3) << 0))

#define AUXR_T0X12_MSK                  BIT7
#define TIMER0_1TMode()                 SET_REG_BIT(AUXR, AUXR_T0X12_MSK)
#define TIMER0_12TMode()                CLR_REG_BIT(AUXR, AUXR_T0X12_MSK)

#define TMOD_T0CT_MSK                   BIT2
#define TIMER0_TimerMode()              CLR_REG_BIT(TMOD, TMOD_T0CT_MSK)
#define TIMER0_CounterMode()            SET_REG_BIT(TMOD, TMOD_T0CT_MSK)

#define TMOD_T0GATE_MSK                 BIT3
#define TIMER0_EnableGateINT0()         SET_REG_BIT(TMOD, TMOD_T0GATE_MSK)
#define TIMER0_DisableGateINT0()        CLR_REG_BIT(TMOD, TMOD_T0GATE_MSK)

#define INTCLKO_T0CLKO_MSK              BIT0
#define TIMER0_EnableCLKO()             SET_REG_BIT(INT_CLKO, INTCLKO_T0CLKO_MSK)
#define TIMER0_DisableCLKO()            CLR_REG_BIT(INT_CLKO, INTCLKO_T0CLKO_MSK)

////////////////////////

#define TIMER1_Run()                    (TR1 = 1)
#define TIMER1_Stop()                   (TR1 = 0)

#define TIMER1_SetReload8(n)            (TH1 = LOBYTE(n), TL1 = LOBYTE(n))
#define TIMER1_SetReload16(n)           (TH1 = HIBYTE(n), TL1 = LOBYTE(n))

#define TMOD_T1M_MSK                    (BIT5 | BIT4)
#define TIMER1_Mode0()                  MODIFY_REG(TMOD, TMOD_T1M_MSK, ((0) << 0))
#define TIMER1_Mode1()                  MODIFY_REG(TMOD, TMOD_T1M_MSK, ((1) << 0))
#define TIMER1_Mode2()                  MODIFY_REG(TMOD, TMOD_T1M_MSK, ((2) << 0))

#define AUXR_T1X12_MSK                  BIT6
#define TIMER1_1TMode()                 SET_REG_BIT(AUXR, AUXR_T1X12_MSK)
#define TIMER1_12TMode()                CLR_REG_BIT(AUXR, AUXR_T1X12_MSK)

#define TMOD_T1CT_MSK                   BIT6
#define TIMER1_TimerMode()              CLR_REG_BIT(TMOD, TMOD_T1CT_MSK)
#define TIMER1_CounterMode()            SET_REG_BIT(TMOD, TMOD_T1CT_MSK)

#define TMOD_T1GATE_MSK                 BIT7
#define TIMER1_EnableGateINT1()         SET_REG_BIT(TMOD, TMOD_T1GATE_MSK)
#define TIMER1_DisableGateINT1()        CLR_REG_BIT(TMOD, TMOD_T1GATE_MSK)

#define INTCLKO_T1CLKO_MSK              BIT1
#define TIMER1_EnableCLKO()             SET_REG_BIT(INT_CLKO, INTCLKO_T1CLKO_MSK)
#define TIMER1_DisableCLKO()            CLR_REG_BIT(INT_CLKO, INTCLKO_T1CLKO_MSK)

////////////////////////

#define AUXR_T2R_MSK                    BIT4
#define TIMER2_Run()                    SET_REG_BIT(AUXR, AUXR_T2R_MSK)
#define TIMER2_Stop()                   CLR_REG_BIT(AUXR, AUXR_T2R_MSK)

#define TIMER2_SetReload16(n)           (T2H = HIBYTE(n), T2L = LOBYTE(n))

#define AUXR_T2X12_MSK                  BIT2
#define TIMER2_1TMode()                 SET_REG_BIT(AUXR, AUXR_T2X12_MSK)
#define TIMER2_12TMode()                CLR_REG_BIT(AUXR, AUXR_T2X12_MSK)

#define AUXR_T2CT_MSK                   BIT3
#define TIMER2_TimerMode()              CLR_REG_BIT(AUXR, AUXR_T2CT_MSK)
#define TIMER2_CounterMode()            SET_REG_BIT(AUXR, AUXR_T2CT_MSK)

#define INTCLKO_T2CLKO_MSK              BIT2
#define TIMER2_EnableCLKO()             SET_REG_BIT(INT_CLKO, INTCLKO_T2CLKO_MSK)
#define TIMER2_DisableCLKO()            CLR_REG_BIT(INT_CLKO, INTCLKO_T2CLKO_MSK)

////////////////////////

#define T4T3M_T3R_MSK                   BIT3
#define TIMER3_Run()                    SET_REG_BIT(T4T3M, T4T3M_T3R_MSK)
#define TIMER3_Stop()                   CLR_REG_BIT(T4T3M, T4T3M_T3R_MSK)

#define TIMER3_SetReload16(n)           (T3H = HIBYTE(n), T3L = LOBYTE(n))

#define T4T3M_T3X12_MSK                 BIT1
#define TIMER3_1TMode()                 SET_REG_BIT(T4T3M, T4T3M_T3X12_MSK)
#define TIMER3_12TMode()                CLR_REG_BIT(T4T3M, T4T3M_T3X12_MSK)

#define T4T3M_T3CT_MSK                  BIT2
#define TIMER3_TimerMode()              CLR_REG_BIT(T4T3M, T4T3M_T3CT_MSK)
#define TIMER3_CounterMode()            SET_REG_BIT(T4T3M, T4T3M_T3CT_MSK)

#define T4T3M_T3CLKO_MSK                BIT0
#define TIMER3_EnableCLKO()             SET_REG_BIT(T4T3M, T4T3M_T3CLKO_MSK)
#define TIMER3_DisableCLKO()            CLR_REG_BIT(T4T3M, T4T3M_T3CLKO_MSK)

////////////////////////

#define T4T3M_T4R_MSK                   BIT7
#define TIMER4_Run()                    SET_REG_BIT(T4T3M, T4T3M_T4R_MSK)
#define TIMER4_Stop()                   CLR_REG_BIT(T4T3M, T4T3M_T4R_MSK)

#define TIMER4_SetReload16(n)           (T4H = HIBYTE(n), T4L = LOBYTE(n))

#define T4T3M_T4X12_MSK                 BIT5
#define TIMER4_1TMode()                 SET_REG_BIT(T4T3M, T4T3M_T4X12_MSK)
#define TIMER4_12TMode()                CLR_REG_BIT(T4T3M, T4T3M_T4X12_MSK)

#define T4T3M_T4CT_MSK                  BIT6
#define TIMER4_TimerMode()              CLR_REG_BIT(T4T3M, T4T3M_T4CT_MSK)
#define TIMER4_CounterMode()            SET_REG_BIT(T4T3M, T4T3M_T4CT_MSK)

#define T4T3M_T4CLKO_MSK                BIT4
#define TIMER4_EnableCLKO()             SET_REG_BIT(T4T3M, T4T3M_T4CLKO_MSK)
#define TIMER4_DisableCLKO()            CLR_REG_BIT(T4T3M, T4T3M_T4CLKO_MSK)

/////////////////////////////////////////////////

#define SCON_SM_MSK                     (BIT7 | BIT6)
#define UART1_SetMode(n)                MODIFY_REG(SCON, SCON_SM_MSK, ((n) << 6))
#define UART1_Mode0()                   UART1_SetMode(0)
#define UART1_Mode1()                   UART1_SetMode(1)
#define UART1_Mode2()                   UART1_SetMode(2)
#define UART1_Mode3()                   UART1_SetMode(3)

#define UART1_EnableRx()                (REN = 1)
#define UART1_DisableRx()               (REN = 0)
#define UART1_SetTB8(b)                 (TB8 = (b))
#define UART1_ReadRB8()                 (RB8)

#define UART1_SendData(d)               (SBUF = (d))
#define UART1_ReadData()                (SBUF)

#define PCON_SMOD_MSK                   BIT7
#define UART1_BaudrateX2()              SET_REG_BIT(PCON, PCON_SMOD_MSK)

#define AUXR_M0X6_MSK                   BIT5
#define UART1_Mode0BaudrateX6()         SET_REG_BIT(AUXR, AUXR_M0X6_MSK)


#define AUXR_S1BRT_MSK                  BIT0
#define UART1_Timer1BRT()               CLR_REG_BIT(AUXR, AUXR_S1BRT_MSK)
#define UART1_Timer2BRT()               SET_REG_BIT(AUXR, AUXR_S1BRT_MSK)

////////////////////////

#define S2CON_S2SM_MSK                  BIT7
#define UART2_SetMode(n)                MODIFY_REG(S2CON, S2CON_S2SM_MSK, ((n) << 7))
#define UART2_Mode0()                   CLR_REG_BIT(S2CON, S2CON_S2SM_MSK)
#define UART2_Mode1()                   SET_REG_BIT(S2CON, S2CON_S2SM_MSK)

#define S2CON_S2REN_MSK                 BIT4
#define UART2_EnableRx()                SET_REG_BIT(S2CON, S2CON_S2REN_MSK)
#define UART2_DisableRx()               CLR_REG_BIT(S2CON, S2CON_S2REN_MSK)

#define S2CON_S2TB8_MSK                 BIT3
#define UART2_SetTB8(b)                 MODIFY_REG(S2CON, S2CON_S2TB8_MSK, ((b) << 3))

#define S2CON_S2RB8_MSK                 BIT2
#define UART2_ReadRB8()                 READ_REG_BIT(S2CON, S2CON_S2RB8_MSK)

#define UART2_SendData(d)               (S2BUF = (d))
#define UART2_ReadData()                (S2BUF)

////////////////////////

#define S3CON_S3SM_MSK                  BIT7
#define UART3_SetMode(n)                MODIFY_REG(S3CON, S3CON_S3SM_MSK, ((n) << 7))
#define UART3_Mode0()                   CLR_REG_BIT(S3CON, S3CON_S3SM_MSK)
#define UART3_Mode1()                   SET_REG_BIT(S3CON, S3CON_S3SM_MSK)

#define S3CON_S3REN_MSK                 BIT4
#define UART3_EnableRx()                SET_REG_BIT(S3CON, S3CON_S3REN_MSK)
#define UART3_DisableRx()               CLR_REG_BIT(S3CON, S3CON_S3REN_MSK)

#define S3CON_S3TB8_MSK                 BIT3
#define UART3_SetTB8(b)                 MODIFY_REG(S3CON, S3CON_S3TB8_MSK, ((b) << 3))

#define S3CON_S3RB8_MSK                 BIT2
#define UART3_ReadRB8()                 READ_REG_BIT(S3CON, S3CON_S3RB8_MSK)

#define UART3_SendData(d)               (S3BUF = (d))
#define UART3_ReadData()                (S3BUF)

#define S3CON_S3BRT_MSK                 BIT6
#define UART3_Timer2BRT()               CLR_REG_BIT(S3CON, S3CON_S3BRT_MSK)
#define UART3_Timer3BRT()               SET_REG_BIT(S3CON, S3CON_S3BRT_MSK)

////////////////////////

#define S4CON_S4SM_MSK                  BIT7
#define UART4_SetMode(n)                MODIFY_REG(S4CON, S4CON_S4SM_MSK, ((n) << 7))
#define UART4_Mode0()                   CLR_REG_BIT(S4CON, S4CON_S4SM_MSK)
#define UART4_Mode1()                   SET_REG_BIT(S4CON, S4CON_S4SM_MSK)

#define S4CON_S4REN_MSK                 BIT4
#define UART4_EnableRx()                SET_REG_BIT(S4CON, S4CON_S4REN_MSK)
#define UART4_DisableRx()               CLR_REG_BIT(S4CON, S4CON_S4REN_MSK)

#define S4CON_S4TB8_MSK                 BIT3
#define UART4_SetTB8(b)                 MODIFY_REG(S4CON, S4CON_S4TB8_MSK, ((b) << 3))

#define S4CON_S4RB8_MSK                 BIT2
#define UART4_ReadRB8()                 READ_REG_BIT(S4CON, S4CON_S4RB8_MSK)

#define UART4_SendData(d)               (S4BUF = (d))
#define UART4_ReadData()                (S4BUF)

#define S4CON_S4BRT_MSK                 BIT6
#define UART4_Timer2BRT()               CLR_REG_BIT(S4CON, S4CON_S4BRT_MSK)
#define UART4_Timer4BRT()               SET_REG_BIT(S4CON, S4CON_S4BRT_MSK)

/////////////////////////////////////////////////

#define CMPCR1_CMPEN_MSK                BIT7
#define CMP_Enable()                    SET_REG_BIT(CMPCR1, CMPCR1_CMPEN_MSK)
#define CMP_Disable()                   CLR_REG_BIT(CMPCR1, CMPCR1_CMPEN_MSK)

#define CMPCR1_CMPOE_MSK                BIT1
#define CMP_EnableOutput()              SET_REG_BIT(CMPCR1, CMPCR1_CMPOE_MSK)
#define CMP_DisableOutput()             CLR_REG_BIT(CMPCR1, CMPCR1_CMPOE_MSK)

#define CMPCR1_CMPRES_MSK               BIT0
#define CMP_ReadResult()                READ_REG_BIT(CMPCR1, CMPCR1_CMPRES_MSK)

#define CMPCR2_INVO_MSK                 BIT7
#define CMP_OutputInvert()              SET_REG_BIT(CMPCR2, CMPCR2_INVO_MSK)

#define CMPCR2_DISFLT_MSK               BIT6
#define CMP_EnableAnalogFilter()        CLR_REG_BIT(CMPCR2, CMPCR2_DISFLT_MSK)
#define CMP_DisableAnalogFilter()       SET_REG_BIT(CMPCR2, CMPCR2_DISFLT_MSK)

#define CMPCR2_LCDTY_MSK                (BIT5 | BIT4 | BIT_LN)
#define CMP_SetDigitalFilter(n)         MODIFY_REG(CMPCR2, CMPCR2_LCDTY_MSK, ((n) << 0))

/////////////////////////////////////////////////

#define IAPCON_IAPEN_MSK                BIT7
#define IAP_Enable()                    SET_REG_BIT(IAP_CONTR, IAPCON_IAPEN_MSK)
#define IAP_Disable()                   CLR_REG_BIT(IAP_CONTR, IAPCON_IAPEN_MSK)

#define IAP_SetData(d)                  (IAP_DATA = (d))
#define IAP_ReadData()                  (IAP_DATA)

#define IAP_SetAddress(n)               IAP_ADDRL = BYTE0(n); \
                                        IAP_ADDRH = BYTE1(n)

#define IAP_Trigger()                   IAP_TRIG = 0x5a; \
                                        IAP_TRIG = 0xa5; \
                                        _nop_();         \
                                        _nop_();         \
                                        _nop_();         \
                                        _nop_()

#define IAP_Idle()                      IAP_CMD = 0
#define IAP_TriggerRead()               IAP_CMD = 1; IAP_Trigger()
#define IAP_TriggerProgram()            IAP_CMD = 2; IAP_Trigger()
#define IAP_TriggerErase()              IAP_CMD = 3; IAP_Trigger()

#define IAPCON_WT_MSK                  	(BIT2 | BIT1 | BIT0)
#define IAP_SetWaitTime(n)              MODIFY_REG(IAP_CONTR, IAPCON_WT_MSK, ((n) << 0))
#define IAP_SetTimeBase()               IAP_SetWaitTime((SYSCLK) <=  1000000 ? 7 : \
                                                        (SYSCLK) <=  2000000 ? 6 : \
                                                        (SYSCLK) <=  3000000 ? 5 : \
                                                        (SYSCLK) <=  6000000 ? 4 : \
                                                        (SYSCLK) <= 12000000 ? 3 : \
                                                        (SYSCLK) <= 20000000 ? 2 : \
                                                        (SYSCLK) <= 24000000 ? 1 : 0)

#define IAPCON_FAIL_MSK                 BIT4
#define IAP_CheckErrorFlag()            READ_REG_BIT(IAP_CONTR, IAPCON_FAIL_MSK)
#define IAP_ClearErrorFlag()            CLR_REG_BIT(IAP_CONTR, IAPCON_FAIL_MSK)

/////////////////////////////////////////////////

#define ADCCONTR_ADCPOWER_MSK           BIT7
#define ADC_Enable()                    SET_REG_BIT(ADC_CONTR, ADCCONTR_ADCPOWER_MSK)
#define ADC_Disable()                   CLR_REG_BIT(ADC_CONTR, ADCCONTR_ADCPOWER_MSK)

#define ADC_ReadResult()                MAKEWORD(ADC_RESL, ADC_RES)

#define ADCCONTR_ADCSTART_MSK           BIT3
#define ADC_Start()                     SET_REG_BIT(ADC_CONTR, ADCCONTR_ADCSTART_MSK)

#define ADCCONTR_ADCCHS_MSK             (BIT2 | BIT1 | BIT0)
#define ADC_ActiveChannel(n)            MODIFY_REG(ADC_CONTR, ADCCONTR_ADCCHS_MSK, ((n) << 0))

#define PWMCFG_CBTADC_MSK               BIT6
#define ADC_EnablePWMTrig()             SET_REG_BIT(PWMCFG, PWMCFG_CBTADC_MSK)

#define CLKDIV_ADRJ_MSK                 BIT5
#define ADC_ResultLeftAlign()           CLR_REG_BIT(CLK_DIV, CLKDIV_ADRJ_MSK)
#define ADC_ResultRightAlign()          SET_REG_BIT(CLK_DIV, CLKDIV_ADRJ_MSK)

#define ADCCONTR_SPEED_MSK              (BIT6 | BIT5)
#define ADC_SetClockDivider(n)          MODIFY_REG(ADC_CONTR, ADCCONTR_SPEED_MSK, ((n) << 5))
#define ADC_SetSpeedTo90Clocks()        ADC_SetClockDivider(3)
#define ADC_SetSpeedTo180Clocks()       ADC_SetClockDivider(2)
#define ADC_SetSpeedTo360Clocks()       ADC_SetClockDivider(1)
#define ADC_SetSpeedTo540Clocks()       ADC_SetClockDivider(0)

/////////////////////////////////////////////////

#define CCON_CR_MSK                     BIT6
#define PCA_Run()                       SET_REG_BIT(CCON, CCON_CR_MSK)
#define PCA_Stop()                      CLR_REG_BIT(CCON, CCON_CR_MSK)

#define CMOD_CIDL_MSK                   BIT7
#define PCA_IdlePause()                 SET_REG_BIT(CMOD, CMOD_CIDL_MSK)
#define PCA_IdleContinue()              CLR_REG_BIT(CMOD, CMOD_CIDL_MSK)

#define CMOD_CPS_MSK                    (BIT3 |BIT2 |BIT1)
#define PCA_SetClockSource(n)           MODIFY_REG(CMOD, CMOD_CPS_MSK, ((n) << 1))
#define PCA_CLK_SYSCLKD12()             PCA_SetClockSource(0)
#define PCA_CLK_SYSCLKD2()              PCA_SetClockSource(1)
#define PCA_CLK_TIMER0OV()              PCA_SetClockSource(2)
#define PCA_CLK_ECI()                   PCA_SetClockSource(3)
#define PCA_CLK_SYSCLK()                PCA_SetClockSource(4)
#define PCA_CLK_SYSCLKD4()              PCA_SetClockSource(5)
#define PCA_CLK_SYSCLKD6()              PCA_SetClockSource(6)
#define PCA_CLK_SYSCLKD8()              PCA_SetClockSource(7)

#define PCA_SetCounter(n)               (CH = HIBYTE(n), CL = LOBYTE(n))
#define PCA_InitCounter()               PCA_SetCounter(0)

#define PCA_SetCnReload(n, v)           CCAP##n##L = LOBYTE(v); \
                                        CCAP##n##H = LOBYTE(v)

#define PCA_SetCnMatch(n, v)            (CCAP##n##L = LOBYTE(v), CCAP##n##H = HIBYTE(v))

#define PCA_ReadCnCapture(n)            MAKEWORD(CCAP##n##L, CCAP##n##H)

#define CCAPMn_ECOM_MSK                 BIT6
#define CCAPMn_CCAPP_MSK                BIT5
#define CCAPMn_CCAPN_MSK                BIT4
#define CCAPMn_MAT_MSK                  BIT3
#define CCAPMn_TOG_MSK                  BIT2
#define CCAPMn_PWM_MSK                  BIT1
#define PCAPWMn_EBS_MSK                 (BIT7 | BIT6)

#define PCA_DisableCn(n)    			CCAPM##n = 0

#define PCA_SetCnAs6BitPWMMode(n)       CCAPM##n = (CCAPMn_ECOM_MSK | CCAPMn_PWM_MSK); \
                                        MODIFY_REG(PCA_PWM##n, PCAPWMn_EBS_MSK, ((2) << 6))
#define PCA_SetCnAs7BitPWMMode(n)       CCAPM##n = (CCAPMn_ECOM_MSK | CCAPMn_PWM_MSK); \
                                        MODIFY_REG(PCA_PWM##n, PCAPWMn_EBS_MSK, ((1) << 6))
#define PCA_SetCnAs8BitPWMMode(n)       CCAPM##n = (CCAPMn_ECOM_MSK | CCAPMn_PWM_MSK); \
                                        MODIFY_REG(PCA_PWM##n, PCAPWMn_EBS_MSK, ((0) << 6))

#define PCA_EnableCnCapturePWMPos(n)    MODIFY_REG(CCAPM##n, CCAPMn_CCAPP_MSK | CCAPMn_CCAPN_MSK, (CCAPMn_CCAPP_MSK))
#define PCA_EnableCnCapturePWMNeg(n)    MODIFY_REG(CCAPM##n, CCAPMn_CCAPP_MSK | CCAPMn_CCAPN_MSK, (CCAPMn_CCAPN_MSK))
#define PCA_EnableCnCapturePWMEdge(n)   CCAPM##n |= (CCAPMn_CCAPP_MSK | CCAPMn_CCAPN_MSK)

#define PCA_SetCnAsCapturePosMode(n)    CCAPM##n = (CCAPMn_CCAPP_MSK)
#define PCA_SetCnAsCaptureNegMode(n)    CCAPM##n = (CCAPMn_CCAPN_MSK)
#define PCA_SetCnAsCaptureEdgeMode(n)   CCAPM##n = (CCAPMn_CCAPP_MSK | CCAPMn_CCAPN_MSK)

#define PCA_SetCnAs16BitTimerMode(n)    CCAPM##n = (CCAPMn_ECOM_MSK | CCAPMn_MAT_MSK)

#define PCA_SetCnAsHighSpeedPulseMode(n) CCAPM##n = (CCAPMn_ECOM_MSK | CCAPMn_MAT_MSK | CCAPMn_TOG_MSK)

#define PCA_DisableC0()              	PCA_DisableCn(0)
#define PCA_DisableC1()              	PCA_DisableCn(1)

#define PCA_SetC0Reload(v)              PCA_SetCnReload(0, (v))
#define PCA_SetC1Reload(v)              PCA_SetCnReload(1, (v))

#define PCA_SetC0Match(v)               PCA_SetCnMatch(0, (v))
#define PCA_SetC1Match(v)               PCA_SetCnMatch(1, (v))

#define PCA_ReadC0Capture()             PCA_ReadCnCapture(0)
#define PCA_ReadC1Capture()             PCA_ReadCnCapture(1)

#define PCA_SetC0As6BitPWMMode()        PCA_SetCnAs6BitPWMMode(0)
#define PCA_SetC1As6BitPWMMode()        PCA_SetCnAs6BitPWMMode(1)

#define PCA_SetC0As7BitPWMMode()        PCA_SetCnAs7BitPWMMode(0)
#define PCA_SetC1As7BitPWMMode()        PCA_SetCnAs7BitPWMMode(1)

#define PCA_SetC0As8BitPWMMode()        PCA_SetCnAs8BitPWMMode(0)
#define PCA_SetC1As8BitPWMMode()        PCA_SetCnAs8BitPWMMode(1)

#define PCA_EnableC0CapturePWMPos()     PCA_EnableCnCapturePWMPos(0)
#define PCA_EnableC1CapturePWMPos()     PCA_EnableCnCapturePWMPos(1)

#define PCA_EnableC0CapturePWMNeg()     PCA_EnableCnCapturePWMNeg(0)
#define PCA_EnableC1CapturePWMNeg()     PCA_EnableCnCapturePWMNeg(1)

#define PCA_EnableC0CapturePWMEdge()    PCA_EnableCnCapturePWMEdge(0)
#define PCA_EnableC1CapturePWMEdge()    PCA_EnableCnCapturePWMEdge(1)

#define PCA_SetC0AsCapturePosMode()     PCA_SetCnAsCapturePosMode(0)
#define PCA_SetC1AsCapturePosMode()     PCA_SetCnAsCapturePosMode(1)

#define PCA_SetC0AsCaptureNegMode()     PCA_SetCnAsCaptureNegMode(0)
#define PCA_SetC1AsCaptureNegMode()     PCA_SetCnAsCaptureNegMode(1)

#define PCA_SetC0AsCaptureEdgeMode()    PCA_SetCnAsCaptureEdgeMode(0)
#define PCA_SetC1AsCaptureEdgeMode()    PCA_SetCnAsCaptureEdgeMode(1)

#define PCA_SetC0As16BitTimerMode()     PCA_SetCnAs16BitTimerMode(0)
#define PCA_SetC1As16BitTimerMode()     PCA_SetCnAs16BitTimerMode(1)

#define PCA_SetC0AsHighSpeedPulseMode() PCA_SetCnAsHighSpeedPulseMode(0)
#define PCA_SetC1AsHighSpeedPulseMode() PCA_SetCnAsHighSpeedPulseMode(1)

/////////////////////////////////////////////////

#define SPCTL_SPEN_MSK                  BIT6
#define SPI_Enable()                    SET_REG_BIT(SPCTL, SPCTL_SPEN_MSK)
#define SPI_Disable()                   CLR_REG_BIT(SPCTL, SPCTL_SPEN_MSK)

#define SPCTL_DORD_MSK                  BIT5
#define SPI_DataLSB()                   SET_REG_BIT(SPCTL, SPCTL_DORD_MSK)
#define SPI_DataMSB()                   CLR_REG_BIT(SPCTL, SPCTL_DORD_MSK)

#define SPCTL_MSTR_MSK                  BIT4
#define SPI_MasterMode()                SET_REG_BIT(SPCTL, SPCTL_MSTR_MSK)
#define SPI_SlaveMode()                 CLR_REG_BIT(SPCTL, SPCTL_MSTR_MSK)

#define SPCTL_SSIG_MSK                  BIT7
#define SPI_IgnoreSS()                  SET_REG_BIT(SPCTL, SPCTL_SSIG_MSK)
#define SPI_UnignoreSS()                CLR_REG_BIT(SPCTL, SPCTL_SSIG_MSK)

#define SPCTL_CPOL_MSK                  BIT3
#define SPCTL_CPHA_MSK                  BIT2
#define SPIMODE                         (SPCTL_CPOL_MSK | SPCTL_CPHA_MSK)
#define SPI_SetMode0()                  MODIFY_REG(SPCTL, SPIMODE, ((0) << 2))
#define SPI_SetMode1()                  MODIFY_REG(SPCTL, SPIMODE, ((1) << 2))
#define SPI_SetMode2()                  MODIFY_REG(SPCTL, SPIMODE, ((2) << 2))
#define SPI_SetMode3()                  MODIFY_REG(SPCTL, SPIMODE, ((3) << 2))

#define SPCTL_SPR_MSK                   (BIT1 | BIT0)
#define SPI_SetClockDivider(n)          MODIFY_REG(SPCTL, SPCTL_SPR_MSK, ((n) << 0))
#define SPI_SetClockDivider4()          SPI_SetClockDivider(0)
#define SPI_SetClockDivider8()          SPI_SetClockDivider(1)
#define SPI_SetClockDivider16()         SPI_SetClockDivider(2)
#define SPI_SetClockDivider32()         SPI_SetClockDivider(3)

#define SPI_SendData(d)                 (SPDAT = (d))
#define SPI_ReadData()                  (SPDAT)

/////////////////////////////////////////////////

#define PWMFDCR_ENFD_MSK                BIT5
#define PWMFD_Enable()                  SET_REG_BIT(PWMFDCR, PWMFDCR_ENFD_MSK)
#define PWMFD_Disable()                 CLR_REG_BIT(PWMFDCR, PWMFDCR_ENFD_MSK)

#define PWMFDCR_FLTFLIO_MSK             BIT4
#define PWMFD_FaltFloatPort()           SET_REG_BIT(PWMFDCR, PWMFDCR_FLTFLIO_MSK)

#define PWMFDCR_FDCMP_MSK               BIT2
#define PWMFD_EnableCMPFalt()           SET_REG_BIT(PWMFDCR, PWMFDCR_FDCMP_MSK)
#define PWMFD_DisableCMPFalt()          CLR_REG_BIT(PWMFDCR, PWMFDCR_FDCMP_MSK)

#define PWMFDCR_FDIO_MSK                BIT1
#define PWMFD_EnablePortFalt()          SET_REG_BIT(PWMFDCR, PWMFDCR_FDIO_MSK)
#define PWMFD_DisablePortFalt()         CLR_REG_BIT(PWMFDCR, PWMFDCR_FDIO_MSK)

#define PWMCR_ENPWM_MAK                 BIT7
#define PWM_Enable()                    SET_REG_BIT(PWMCR, PWMCR_ENPWM_MAK)
#define PWM_Disable()                   CLR_REG_BIT(PWMCR, PWMCR_ENPWM_MAK)

#define PWMCR_ENC2O_MSK                 BIT0
#define PWMCR_ENC3O_MSK                 BIT1
#define PWMCR_ENC4O_MSK                 BIT2
#define PWMCR_ENC5O_MSK                 BIT3
#define PWMCR_ENC6O_MSK                 BIT4
#define PWMCR_ENC7O_MSK                 BIT5
#define PWM_EnableC2Output()            SET_REG_BIT(PWMCR, PWMCR_ENC2O_MSK)
#define PWM_EnableC3Output()            SET_REG_BIT(PWMCR, PWMCR_ENC3O_MSK)
#define PWM_EnableC4Output()            SET_REG_BIT(PWMCR, PWMCR_ENC4O_MSK)
#define PWM_EnableC5Output()            SET_REG_BIT(PWMCR, PWMCR_ENC5O_MSK)
#define PWM_EnableC6Output()            SET_REG_BIT(PWMCR, PWMCR_ENC6O_MSK)
#define PWM_EnableC7Output()            SET_REG_BIT(PWMCR, PWMCR_ENC7O_MSK)
#define PWM_DisableC2Output()           CLR_REG_BIT(PWMCR, PWMCR_ENC2O_MSK)
#define PWM_DisableC3Output()           CLR_REG_BIT(PWMCR, PWMCR_ENC3O_MSK)
#define PWM_DisableC4Output()           CLR_REG_BIT(PWMCR, PWMCR_ENC4O_MSK)
#define PWM_DisableC5Output()           CLR_REG_BIT(PWMCR, PWMCR_ENC5O_MSK)
#define PWM_DisableC6Output()           CLR_REG_BIT(PWMCR, PWMCR_ENC6O_MSK)
#define PWM_DisableC7Output()           CLR_REG_BIT(PWMCR, PWMCR_ENC7O_MSK)

#define PWMCFG_C2INI_MSK                BIT0
#define PWMCFG_C3INI_MSK                BIT1
#define PWMCFG_C4INI_MSK                BIT2
#define PWMCFG_C5INI_MSK                BIT3
#define PWMCFG_C6INI_MSK                BIT4
#define PWMCFG_C7INI_MSK                BIT5
#define PWM_InitialC2High()             SET_REG_BIT(PWMCFG, PWMCFG_C2INI_MSK)
#define PWM_InitialC3High()             SET_REG_BIT(PWMCFG, PWMCFG_C3INI_MSK)
#define PWM_InitialC4High()             SET_REG_BIT(PWMCFG, PWMCFG_C4INI_MSK)
#define PWM_InitialC5High()             SET_REG_BIT(PWMCFG, PWMCFG_C5INI_MSK)
#define PWM_InitialC6High()             SET_REG_BIT(PWMCFG, PWMCFG_C6INI_MSK)
#define PWM_InitialC7High()             SET_REG_BIT(PWMCFG, PWMCFG_C7INI_MSK)
#define PWM_InitialC2Low()              CLR_REG_BIT(PWMCFG, PWMCFG_C2INI_MSK)
#define PWM_InitialC3Low()              CLR_REG_BIT(PWMCFG, PWMCFG_C3INI_MSK)
#define PWM_InitialC4Low()              CLR_REG_BIT(PWMCFG, PWMCFG_C4INI_MSK)
#define PWM_InitialC5Low()              CLR_REG_BIT(PWMCFG, PWMCFG_C5INI_MSK)
#define PWM_InitialC6Low()              CLR_REG_BIT(PWMCFG, PWMCFG_C6INI_MSK)
#define PWM_InitialC7Low()              CLR_REG_BIT(PWMCFG, PWMCFG_C7INI_MSK)

#define PWMCFG_CBTADC_MSK               BIT6
#define PWM_EnableTriggerADC()          SET_REG_BIT(PWMCFG, PWMCFG_CBTADC_MSK)
#define PWM_DisableTriggerADC()         CLR_REG_BIT(PWMCFG, PWMCFG_CBTADC_MSK)

#define PWMCKS_SELT2_MSK                BIT4
#define PWM_CLK_SYSCLK()                CLR_REG_BIT(PWMCKS, PWMCKS_SELT2_MSK)
#define PWM_CLK_Timer2()                SET_REG_BIT(PWMCKS, PWMCKS_SELT2_MSK)

#define PWMCKS_SYSCLKPS_MSK             (BIT_LN)
#define PWM_SetClockDivider(n)          MODIFY_REG(PWMCKS, PWMCKS_SYSCLKPS_MSK, ((n) << 0))

#define PWM_SetCounter(n)               (PWMCH = HIBYTE(n), PWMCL = LOBYTE(n))
#define PWM_SetC2T1Point(n)             (PWM2T1H = HIBYTE(n), PWM2T1L = LOBYTE(n))
#define PWM_SetC2T2Point(n)             (PWM2T2H = HIBYTE(n), PWM2T2L = LOBYTE(n))
#define PWM_SetC3T1Point(n)             (PWM3T1H = HIBYTE(n), PWM3T1L = LOBYTE(n))
#define PWM_SetC3T2Point(n)             (PWM3T2H = HIBYTE(n), PWM3T2L = LOBYTE(n))
#define PWM_SetC4T1Point(n)             (PWM4T1H = HIBYTE(n), PWM4T1L = LOBYTE(n))
#define PWM_SetC4T2Point(n)             (PWM4T2H = HIBYTE(n), PWM4T2L = LOBYTE(n))
#define PWM_SetC5T1Point(n)             (PWM5T1H = HIBYTE(n), PWM5T1L = LOBYTE(n))
#define PWM_SetC5T2Point(n)             (PWM5T2H = HIBYTE(n), PWM5T2L = LOBYTE(n))
#define PWM_SetC6T1Point(n)             (PWM6T1H = HIBYTE(n), PWM6T1L = LOBYTE(n))
#define PWM_SetC6T2Point(n)             (PWM6T2H = HIBYTE(n), PWM6T2L = LOBYTE(n))
#define PWM_SetC7T1Point(n)             (PWM7T1H = HIBYTE(n), PWM7T1L = LOBYTE(n))
#define PWM_SetC7T2Point(n)             (PWM7T2H = HIBYTE(n), PWM7T2L = LOBYTE(n))

/////////////////////////////////////////////////
//Interrupt Vector
/////////////////////////////////////////////////

#define     INT0_VECTOR             0       //0003H
#define     TMR0_VECTOR             1       //000BH
#define     INT1_VECTOR             2       //0013H
#define     TMR1_VECTOR             3       //001BH
#define     UART1_VECTOR            4       //0023H
#define     ADC_VECTOR              5       //002BH
#define     LVD_VECTOR              6       //0033H
#define     PCA_VECTOR              7       //003BH
#define     UART2_VECTOR            8       //0043H
#define     SPI_VECTOR              9       //004BH
#define     INT2_VECTOR             10      //0053H
#define     INT3_VECTOR             11      //005BH
#define     TMR2_VECTOR             12      //0063H
#define     USER_VECTOR             13      //006BH
#define     INT4_VECTOR             16      //0083H
#define     UART3_VECTOR            17      //008BH
#define     UART4_VECTOR            18      //0093H
#define     TMR3_VECTOR             19      //009BH
#define     TMR4_VECTOR             20      //00A3H
#define     CMP_VECTOR              21      //00ABH
#define     PWM_VECTOR              22      //00B3H
#define     PWMFD_VECTOR            23      //00BBH

/////////////////////////////////////////////////

#define NOP1()  _nop_()
#define NOP2()  NOP1(),NOP1()
#define NOP3()  NOP2(),NOP1()
#define NOP4()  NOP3(),NOP1()
#define NOP5()  NOP4(),NOP1()
#define NOP6()  NOP5(),NOP1()
#define NOP7()  NOP6(),NOP1()
#define NOP8()  NOP7(),NOP1()
#define NOP9()  NOP8(),NOP1()
#define NOP10() NOP9(),NOP1()
#define NOP11() NOP10(),NOP1()
#define NOP12() NOP11(),NOP1()
#define NOP13() NOP12(),NOP1()
#define NOP14() NOP13(),NOP1()
#define NOP15() NOP14(),NOP1()
#define NOP16() NOP15(),NOP1()
#define NOP17() NOP16(),NOP1()
#define NOP18() NOP17(),NOP1()
#define NOP19() NOP18(),NOP1()
#define NOP20() NOP19(),NOP1()
#define NOP21() NOP20(),NOP1()
#define NOP22() NOP21(),NOP1()
#define NOP23() NOP22(),NOP1()
#define NOP24() NOP23(),NOP1()
#define NOP25() NOP24(),NOP1()
#define NOP26() NOP25(),NOP1()
#define NOP27() NOP26(),NOP1()
#define NOP28() NOP27(),NOP1()
#define NOP29() NOP28(),NOP1()
#define NOP30() NOP29(),NOP1()
#define NOP31() NOP30(),NOP1()
#define NOP32() NOP31(),NOP1()
#define NOP33() NOP32(),NOP1()
#define NOP34() NOP33(),NOP1()
#define NOP35() NOP34(),NOP1()
#define NOP36() NOP35(),NOP1()
#define NOP37() NOP36(),NOP1()
#define NOP38() NOP37(),NOP1()
#define NOP39() NOP38(),NOP1()
#define NOP40() NOP39(),NOP1()
#define NOP(N)  NOP##N()

/////////////////////////////////////////////////


#endif

