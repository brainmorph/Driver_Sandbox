/*
 * dc_gpio_driver.h
 *
 *  Created on: Nov 22, 2020
 *      Author: DC
 */

#ifndef DC_GPIO_DRIVER_H_
#define DC_GPIO_DRIVER_H_


#include <stdint.h>

void DGD_Initialize(uint32_t *regAddr);
void DGD_SetBit(uint32_t *address, uint8_t bit);
void DGD_ClearBit(uint32_t *address, uint8_t bit);


#endif /* DC_GPIO_DRIVER_H_ */
