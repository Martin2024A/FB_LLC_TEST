# ȫ�ֽṹ�����

## 1. FILTER_PMBUS_REGS

### 1.1 filter0_pmbus_regs_constants
constant_data-->filter0_pmbus_regs_constants
> λ��flash
&filter0_pmbus_regs_constants-->&filter0_pmbus_regs
> RAM Ϊfilter���ò���
### 1.2 filter0_start_up_pmbus_regs_constants
filter0_start_up_pmbus_regs
> ����filter����ѡ��
### 1.3 filter0_cp_pmbus_regs_constants
filter0_cp_pmbus_regs
### 1.4 filter1_pmbus_regs_constants
filter1_pmbus_regs

## 2. PMBUS_DCDC_CAL
## 3. PMBUS_DCDC_CAL_NONPAGED
## 4. PMBUS_DCDC_CONFIG
> ��Ҫ���˴˽ṹ����� ���ò���
## 5. PMBUS_DCDC_CONFIG_NONPAGED

## 6. 
EXTERN ADC_VALUES_STRUCT adc_values; 	//ADC Readings
EXTERN ADC_VALUES_STRUCT adc_values_avg;//ADC Readings Averaged
EXTERN FIQ_DATA fiq_data;
