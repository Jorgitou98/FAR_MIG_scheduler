#ifndef MIG_MANAGER_H
#define MIG_MANAGER_H

#include <iostream>
#include <string>
#include <nvml.h>
#include "utils.h"

void init_nvml();
nvmlDevice_t bind_device(int gpu_number);
string get_gpu_name(nvmlDevice_t device);
void MIG_enable(nvmlDevice_t device, int gpu_number);
void MIG_disable(nvmlDevice_t device, int gpu_number);

void destroy_all_instances(nvmlDevice_t device);
void create_instance(nvmlDevice_t device, Instance & instance);
void destroy_instance(Instance const& instance);

#endif