/*
 * name:        LC709203F
 * description: Smart LiB Gauge Battery Fuel Gauge LSI For 1‐Cell Lithium‐ion/Polymer (Li+)
 * manuf:       ON Semiconductor
 * version:     0.1
 * url:         http://www.onsemi.com/pub/Collateral/LC709203F-D.PDF
 * date:        2017-12-29
 * author       https://chisl.io/
 * file:        LC709203F.hpp
 */

#include <cinttypes>

/* Derive from class LC709203F_Base and implement the read and write functions! */

/* LC709203F: Smart LiB Gauge Battery Fuel Gauge LSI For 1‐Cell Lithium‐ion/Polymer (Li+) */
class LC709203F_Base
{
public:
	/* Pure virtual functions that need to be implemented in derived class: */
	virtual uint8_t read8(uint16_t address, uint16_t n=8) = 0;  // 8 bit read
	virtual void write(uint16_t address, uint8_t value, uint16_t n=8) = 0;  // 8 bit write
	virtual uint16_t read16(uint16_t address, uint16_t n=16) = 0;  // 16 bit read
	virtual void write(uint16_t address, uint16_t value, uint16_t n=16) = 0;  // 16 bit write
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                         REG BEFORE_RSOC                                          *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG BEFORE_RSOC:
	 * Executes RSOC initialization with sampled maximum voltage when 'hAA55 is set.
	 * This LSI obtains Open Circuit Voltage (OCV) reading
	 * 10 ms after Power-on reset to initialize RSOC (See
	 * Figure 7).
	 * Or the LSI can be forced to initialize RSOC by sending the
	 * Before RSOC Command (0×04 = AA55) or the Initial
	 * RSOC Command (0×07 = AA55). The accuracy of the
	 * Initialization requires the OCV reading to be taken with
	 * minimal load or charge, under 0.025C, on the battery. (i.e.
	 * less than 75 mA for 3000 mAh design capacity battery.).
	 * The LSI initializes RSOC by the maximum voltage
	 * between initialize after Power-on reset and setting the
	 * command when the Before RSOC command is written. (See
	 * Figure 8).
	 */
	struct BEFORE_RSOC
	{
		static const uint16_t __address = 4;
		
		/* Bits BEFORE_RSOC: */
		struct BEFORE_RSOC_
		{
			/* Mode:w */
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
		static const uint16_t INIT_RSOC = 0xaa55; // Initialize RSOC
	};
	
	/* Set register BEFORE_RSOC */
	void setBEFORE_RSOC(uint16_t value)
	{
		write(BEFORE_RSOC::__address, value, 16);
	}
	
	/* Get register BEFORE_RSOC */
	uint16_t getBEFORE_RSOC()
	{
		return read16(BEFORE_RSOC::__address, 16);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                         REG THERMISTOR_B                                          *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG THERMISTOR_B:
	 * Sets B−constant of the thermistor to be measured.
	 * Units: 1K
	 * Refer to
	 * the specification sheet of the thermistor for the set value to
	 * use.
	 */
	struct THERMISTOR_B
	{
		static const uint16_t __address = 6;
		
		/* Bits THERMISTOR_B: */
		struct THERMISTOR_B_
		{
			/* Mode:rw */
			static const uint16_t dflt = 0b0000110100110100; // 16'hd34
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
	};
	
	/* Set register THERMISTOR_B */
	void setTHERMISTOR_B(uint16_t value)
	{
		write(THERMISTOR_B::__address, value, 16);
	}
	
	/* Get register THERMISTOR_B */
	uint16_t getTHERMISTOR_B()
	{
		return read16(THERMISTOR_B::__address, 16);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                         REG INITIAL_RSOC                                          *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG INITIAL_RSOC:
	 * Executes RSOC initialization when 0xAA55 is set.
	 * The LSI can be forced to initialize RSOC by sending the Before RSOC Command (0×04 = AA55)
	 * or the Initial RSOC Command (0×07 = AA55).
	 * The LSI initializes RSOC by the measured voltage at that time when the Initial RSOC command
	 * is written. (See Figure 9). The maximum time to initialize RSOC after the command is
	 * written is 1.5 ms.
	 */
	struct INITIAL_RSOC
	{
		static const uint16_t __address = 7;
		
		/* Bits INIT_RSOC: */
		struct INIT_RSOC
		{
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
			static const uint16_t INIT_RSOC_ = 0xaa55; // Initialize RSOC
		};
	};
	
	/* Set register INITIAL_RSOC */
	void setINITIAL_RSOC(uint16_t value)
	{
		write(INITIAL_RSOC::__address, value, 16);
	}
	
	/* Get register INITIAL_RSOC */
	uint16_t getINITIAL_RSOC()
	{
		return read16(INITIAL_RSOC::__address, 16);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                REG CELL_TEMPERATURE, variant SPI                                 *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG CELL_TEMPERATURE_SPI:
	 * Displays Cell Temperature, 0x0000 to 0xFFFF.
	 * Units: 0.1K (0.0°C = 0x0AAC)
	 * This register contains the cell temperature from −20_C (0×09E4) to +60_C (0×0D04) measured in 0.1_C units.
	 * In the Thermistor mode (0×16 = 01) the LSI measures the attached thermistor and loads the temperature into the Cell Temperature register. In the Thermistor mode, the thermistor shall be connected to the LSI as shown in Figure 2. The temperature is measured by having TSW pin to provide power into the thermistor and TSENSE pin to sense the output voltage from the thermistor. Temperature measurement timing is controlled by the LSI, and the power to the thermistor is not supplied for other reasons except to measure the temperature.
	 */
	struct CELL_TEMPERATURE_SPI
	{
		static const uint16_t __address = 8;
		
		/* Bits CELL_TEMPERATURE: */
		struct CELL_TEMPERATURE
		{
			/* Mode:r */
			static const uint16_t dflt = 0b0000101110100110; // 16'hba6
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
	};
	
	/* Set register CELL_TEMPERATURE_SPI */
	void setCELL_TEMPERATURE_SPI(uint16_t value)
	{
		write(CELL_TEMPERATURE_SPI::__address, value, 16);
	}
	
	/* Get register CELL_TEMPERATURE */
	uint16_t getCELL_TEMPERATURE_SPI()
	{
		return read16(CELL_TEMPERATURE_SPI::__address, 16);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                REG CELL_TEMPERATURE, variant I2C                                 *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG CELL_TEMPERATURE_I2C:
	 * Sets Cell Temperature in I2C mode, h09E4 to 'h0D04.
	 * Units: 0.1K (0.0°C = 0x0AAC)
	 * This register contains the cell temperature from −20_C (0×09E4) to +60_C (0×0D04) measured in 0.1_C units.
	 * In the I2C mode (0×16 = 00) the temperature is provided by the host processor. During discharge/charge the register should be updates when the temperature changes more than 1_C
	 */
	struct CELL_TEMPERATURE_I2C
	{
		static const uint16_t __address = 8;
		
		/* Bits CELL_TEMPERATURE: */
		struct CELL_TEMPERATURE
		{
			/* Mode:w */
			static const uint16_t dflt = 0b0000101110100110; // 16'hba6
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
	};
	
	/* Set register CELL_TEMPERATURE_I2C */
	void setCELL_TEMPERATURE_I2C(uint16_t value)
	{
		write(CELL_TEMPERATURE_I2C::__address, value, 16);
	}
	
	/* Get register CELL_TEMPERATURE */
	uint16_t getCELL_TEMPERATURE_I2C()
	{
		return read16(CELL_TEMPERATURE_I2C::__address, 16);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                        REG CELL_VOLTAGGE                                         *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG CELL_VOLTAGGE:
	 * Displays Cell Voltage, 'h0000 to 'hFFFF.
	 * Units: 1 mV Displays Cell Voltage
	 * This register contains the voltage on VDD 1 mV units.
	 */
	struct CELL_VOLTAGGE
	{
		static const uint16_t __address = 9;
		
		/* Bits CELL_VOLTAGGE: */
		struct CELL_VOLTAGGE_
		{
			/* Mode:r */
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register CELL_VOLTAGGE */
	void setCELL_VOLTAGGE(uint8_t value)
	{
		write(CELL_VOLTAGGE::__address, value, 8);
	}
	
	/* Get register CELL_VOLTAGGE */
	uint8_t getCELL_VOLTAGGE()
	{
		return read8(CELL_VOLTAGGE::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                      REG CURRENT_DIRECTION                                       *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG CURRENT_DIRECTION:
	 * Selects Auto/Charge/Discharge mode
	 */
	struct CURRENT_DIRECTION
	{
		static const uint16_t __address = 10;
		
		/* Bits CURRENT_DIRECTION: */
		struct CURRENT_DIRECTION_
		{
			/* Mode:rw */
			static const uint16_t dflt = 0b0000000000000000; // 16'h0
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
		static const uint16_t AUTO_MODE = 0x00; // 
		static const uint16_t CHARGE_MODE = 0x01; // 
		static const uint16_t DISCHARGE_MODE = 0xffff; // 
	};
	
	/* Set register CURRENT_DIRECTION */
	void setCURRENT_DIRECTION(uint16_t value)
	{
		write(CURRENT_DIRECTION::__address, value, 16);
	}
	
	/* Get register CURRENT_DIRECTION */
	uint16_t getCURRENT_DIRECTION()
	{
		return read16(CURRENT_DIRECTION::__address, 16);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                             REG APA                                              *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG APA:
	 * Adjustment Pack Application: Sets Parasitic impedance, 'h0000 to 'h00FF.
	 * Units: 1 mΩ
	 * This register is used to control the reporting of RSOC. In Auto mode the RSOC is reported as it increases or decreases. In Charge mode the RSOC is not permitted to decrease. In Discharge mode the RSOC is not permitted to increase.
	 * With consideration of capacity influence by temperature, we recommend operating in Auto because RSOC is affected by the cell temperature. A warm cell has more capacity than a cold cell. Be sure not to charge in the Discharge mode and discharge in the Charge mode; it will create an error.
	 * An example of RSOC reporting is shown in Figures 10 and 11.
	 */
	struct APA
	{
		static const uint16_t __address = 11;
		
		/* Bits APA: */
		struct APA_
		{
			/* Mode:rw */
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register APA */
	void setAPA(uint8_t value)
	{
		write(APA::__address, value, 8);
	}
	
	/* Get register APA */
	uint8_t getAPA()
	{
		return read8(APA::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                             REG APT                                              *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG APT:
	 * Adjustment Pack Thermistor: Sets a value to adjust temperature measurement
	 * delay timing, 'h0000 to 'hFFFF
	 */
	struct APT
	{
		static const uint16_t __address = 12;
		
		/* Bits APT: */
		struct APT_
		{
			/* Mode:rw */
			static const uint16_t dflt = 0b0000000000011110; // 16'h1e
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
	};
	
	/* Set register APT */
	void setAPT(uint16_t value)
	{
		write(APT::__address, value, 16);
	}
	
	/* Get register APT */
	uint16_t getAPT()
	{
		return read16(APT::__address, 16);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                             REG RSOC                                              *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG RSOC:
	 * Displays RSOC value based on a 0−100 scale, 'h0000 to 'h0064.
	 * Units: 1%.
	 */
	struct RSOC
	{
		static const uint16_t __address = 13;
		
		/* Bits RSOC: */
		struct RSOC_
		{
			/* Mode:r */
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register RSOC */
	void setRSOC(uint8_t value)
	{
		write(RSOC::__address, value, 8);
	}
	
	/* Get register RSOC */
	uint8_t getRSOC()
	{
		return read8(RSOC::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                             REG ITE                                              *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG ITE:
	 * Indicator to Empty: 1% Displays RSOC value based on a 0−100 scale, 'h0000 to 'h03E8 .
	 * Units: 0.1%.
	 * This is the same as RSOC with a resolution of 0.1% over the range 0.0% to 100.0%.
	 */
	struct ITE
	{
		static const uint16_t __address = 15;
		
		/* Bits ITE: */
		struct ITE_
		{
			/* Mode:r */
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register ITE */
	void setITE(uint8_t value)
	{
		write(ITE::__address, value, 8);
	}
	
	/* Get register ITE */
	uint8_t getITE()
	{
		return read8(ITE::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG IC_VERSION                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG IC_VERSION:
	 * Displays an ID number of an IC, 'h0000 to 'hFFFF.
	 */
	struct IC_VERSION
	{
		static const uint16_t __address = 17;
		
		/* Bits IC_VERSION: */
		struct IC_VERSION_
		{
			/* Mode:r */
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register IC_VERSION */
	void setIC_VERSION(uint8_t value)
	{
		write(IC_VERSION::__address, value, 8);
	}
	
	/* Get register IC_VERSION */
	uint8_t getIC_VERSION()
	{
		return read8(IC_VERSION::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                       REG CHANGE_OF_PARAM                                        *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG CHANGE_OF_PARAM:
	 * Change Of The Parameter Selects a battery profile, 0x0000 or 0x0001
	 * The LSI contains a data file comprised of two battery profiles. This register is used to select the battery profile to be used. See Table 8. Register Number of the Parameter (0x1A) contains identity of the data file.
	 * The Data file is loaded during final test depending on the part number ordered.
	 * Most of the time, battery nominal/rated voltage or charging voltage values are used to determine which profile data shall be used. Please contact ON Semiconductor if you cannot identify which profile to select.
	 */
	struct CHANGE_OF_PARAM
	{
		static const uint16_t __address = 18;
		
		/* Bits CHANGE_OF_PARAM: */
		struct CHANGE_OF_PARAM_
		{
			/* Mode: */
			static const uint16_t dflt = 0b0000000000000000; // 16'h0
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
	};
	
	/* Set register CHANGE_OF_PARAM */
	void setCHANGE_OF_PARAM(uint16_t value)
	{
		write(CHANGE_OF_PARAM::__address, value, 16);
	}
	
	/* Get register CHANGE_OF_PARAM */
	uint16_t getCHANGE_OF_PARAM()
	{
		return read16(CHANGE_OF_PARAM::__address, 16);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                        REG ALARM_LOW_RSOC                                         *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG ALARM_LOW_RSOC:
	 * Alarm Low RSO: Disable Sets RSOC threshold to generate Alarm signal.
	 * Units: 1%
	 * The ALARMB pin will be set low when the RSOC value falls below this value, will be released from low when RSOC value rises than this value. Set to Zero to disable. Figure 14.
	 */
	struct ALARM_LOW_RSOC
	{
		static const uint16_t __address = 19;
		
		/* Bits ALARM_LOW_RSOC: */
		struct ALARM_LOW_RSOC_
		{
			/* Mode:rw */
			static const uint16_t dflt = 0b0000000000001000; // 16'h8
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
		static const uint16_t Disable = 0x00; // 0x0001 to 0x0064: Threshold §
	};
	
	/* Set register ALARM_LOW_RSOC */
	void setALARM_LOW_RSOC(uint16_t value)
	{
		write(ALARM_LOW_RSOC::__address, value, 16);
	}
	
	/* Get register ALARM_LOW_RSOC */
	uint16_t getALARM_LOW_RSOC()
	{
		return read16(ALARM_LOW_RSOC::__address, 16);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                    REG ALARM_LOW_CELL_VOLTAGE                                     *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG ALARM_LOW_CELL_VOLTAGE:
	 * Alarm Low Cell: Disable	1 mV Sets Voltage threshold to generate Alarm signal.
	 * Units: 1mV.
	 * The ALARMB pin will be set low if VDD falls below this value, will be released from low if VDD rises than this value. Set to Zero to disable. Figure 15.
	 */
	struct ALARM_LOW_CELL_VOLTAGE
	{
		static const uint16_t __address = 20;
		
		/* Bits ALARM_LOW_CELL_VOLTAGE: */
		struct ALARM_LOW_CELL_VOLTAGE_
		{
			/* Mode:rw */
			static const uint16_t dflt = 0b0000000000000000; // 16'h0
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
		static const uint16_t DISABLE = 0x00; // 0x0001 to 0xFFFF: Threshold
	};
	
	/* Set register ALARM_LOW_CELL_VOLTAGE */
	void setALARM_LOW_CELL_VOLTAGE(uint16_t value)
	{
		write(ALARM_LOW_CELL_VOLTAGE::__address, value, 16);
	}
	
	/* Get register ALARM_LOW_CELL_VOLTAGE */
	uint16_t getALARM_LOW_CELL_VOLTAGE()
	{
		return read16(ALARM_LOW_CELL_VOLTAGE::__address, 16);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                        REG IC_POWER_MODE                                         *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG IC_POWER_MODE:
	 * IC Power Mode: Selects Power mode. See note 4.
	 * The LSI has two power modes. Sleep (0x15 = 02) or Operational mode (0x15 = 01). In the Sleep mode only I2C communication functions. In the Operational mode all functions operate with full calculation and tracking of RSOC during charge and discharge.
	 * If the battery is significantly charged or discharged during sleep mode, the RSOC will not be accurate. Moved charge is counted continuously to measure the RSOC in
	 * Operational mode. If battery is discharged or charged in the Sleep mode, the count breaks off.
	 * When it is switched from Sleep mode to Operational mode, RSOC calculation is continued by using the data which was measured in the previous Operational mode.
	 */
	struct IC_POWER_MODE
	{
		static const uint16_t __address = 21;
		
		/* Bits IC_POWER_MODE: */
		struct IC_POWER_MODE_
		{
			/* Mode: */
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
		static const uint16_t Operational_Mode = 0x01; // 
		static const uint16_t Sleep_Mode = 0x02; // 
	};
	
	/* Set register IC_POWER_MODE */
	void setIC_POWER_MODE(uint16_t value)
	{
		write(IC_POWER_MODE::__address, value, 16);
	}
	
	/* Get register IC_POWER_MODE */
	uint16_t getIC_POWER_MODE()
	{
		return read16(IC_POWER_MODE::__address, 16);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG STATUS_BIT                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG STATUS_BIT:
	 * Status Bit: Selects Temperature obtaining method.
	 * This selects the Thermistor mode. Thermistor mode (0x16 = 01) the LSI measures the attached thermistor and loads the temperature into the Cell Temperature register.
	 * I2C mode (0x16 = 00) the temperature is provided by the host processor.
	 */
	struct STATUS_BIT
	{
		static const uint16_t __address = 22;
		
		/* Bits STATUS_BIT: */
		struct STATUS_BIT_
		{
			/* Mode:rw */
			static const uint16_t dflt = 0b0000000000000000; // 16'h0
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
		static const uint16_t I2C_MODE = 0x00; // 
		static const uint16_t THERMISTOR_MODE = 0x01; // 
	};
	
	/* Set register STATUS_BIT */
	void setSTATUS_BIT(uint16_t value)
	{
		write(STATUS_BIT::__address, value, 16);
	}
	
	/* Get register STATUS_BIT */
	uint16_t getSTATUS_BIT()
	{
		return read16(STATUS_BIT::__address, 16);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                   REG NUMBER_OF_THE_PARAMETER                                    *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG NUMBER_OF_THE_PARAMETER:
	 * Number of The	Parameter: Displays Battery profile code
	 * The LSI contains a data file comprised of two battery profiles. This register contains identity of the data file. Please see register Change of the Parameter (0x12) to select the battery profile to be used. See Table 8.
	 * The Data file is loaded during final test depending on the part number ordered. This file can be loaded in the field if required.
	 * Please contact ON Semiconductor if you cannot identify which profile to select.
	 */
	struct NUMBER_OF_THE_PARAMETER
	{
		static const uint16_t __address = 26;
		
		/* Bits NUMBER_OF_THE_PARAMETER: */
		struct NUMBER_OF_THE_PARAMETER_
		{
			/* Mode:r */
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
		static const uint16_t LC709203Fxx_01xx = 0x301; // See table 8
		static const uint16_t LC709203Fxx_03xx = 0x601; // See table 8
		static const uint16_t LC709203Fxx_04xx = 0x504; // See table 8
		static const uint16_t LC709203Fxx_05xx = 0x706; // See table 8
	};
	
	/* Set register NUMBER_OF_THE_PARAMETER */
	void setNUMBER_OF_THE_PARAMETER(uint16_t value)
	{
		write(NUMBER_OF_THE_PARAMETER::__address, value, 16);
	}
	
	/* Get register NUMBER_OF_THE_PARAMETER */
	uint16_t getNUMBER_OF_THE_PARAMETER()
	{
		return read16(NUMBER_OF_THE_PARAMETER::__address, 16);
	}
	
};
