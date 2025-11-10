add_executable(adc_nct_thermistor
        adc_nct_thermistor.c
        )

target_link_libraries(adc_nct_thermistor pico_stdlib hardware_adc)

# create map/bin/hex file etc.
pico_add_extra_outputs(adc_nct_thermistor)

# add url via pico_set_program_url
example_auto_set_url(adc_nct_thermistor)

