#include "error_handler.h"

ERROR_STATUS_T error_vector[ERROR_NUM_ERRORS];

ERROR_HANDLER_STATUS_T handle_LTC6804_PEC(ERROR_STATUS_T* er_stat, uint32_t msTicks);
ERROR_HANDLER_STATUS_T handle_ERROR(ERROR_STATUS_T* er_stat, uint32_t msTicks);
ERROR_HANDLER_STATUS_T handle_INVALID_SSM_STATE(ERROR_STATUS_T* er_stat, uint32_t msTicks);
ERROR_HANDLER_STATUS_T handle_CONTACTORS_ERRONEOUS_STATE(ERROR_STATUS_T* er_stat, uint32_t msTicks);
ERROR_HANDLER_STATUS_T handle_CELL_UNDER_VOLTAGE(ERROR_STATUS_T* er_stat, uint32_t msTicks);
ERROR_HANDLER_STATUS_T handle_CELL_OVER_VOLTAGE(ERROR_STATUS_T* er_stat, uint32_t msTicks);
ERROR_HANDLER_STATUS_T handle_CELL_OVER_TEMP(ERROR_STATUS_T* er_stat, uint32_t msTicks);
ERROR_HANDLER_STATUS_T handle_OVER_CURRENT(ERROR_STATUS_T* er_stat, uint32_t msTicks);

ERROR_HANDLER error_handler_vector[ERROR_NUM_ERRORS] = {handle_LTC6804_PEC,
														handle_ERROR,
														handle_INVALID_SSM_STATE,
														handle_CONTACTORS_ERRONEOUS_STATE,
														handle_CELL_UNDER_VOLTAGE,
														handle_CELL_OVER_VOLTAGE,
														handle_CELL_OVER_TEMP,
														handle_OVER_CURRENT};


void Error_Assert(ERROR_T er_t, uint32_t msTicks) {
	if (error_vector[er_t].error == false) {
		error_vector[er_t].error = true;
		error_vector[er_t].time_stamp = msTicks;
		error_vector[er_t].count = 1;
	}
	else {
		error_vector[er_t].count+=1;
	}

}
void Error_Pass(ERROR_T er_t, uint32_t msTicks) {
	error_vector[er_t].error = false;
}

ERROR_HANDLER_STATUS_T Error_Handle(uint32_t msTicks) {
	ERROR_T i;
	for (i = 0; i < ERROR_NUM_ERRORS; ++i) {
		if (error_vector[i].error == true) {
			error_handler_vector[i](&error_vector[i], msTicks);
		}
	}
}

ERROR_HANDLER_STATUS_T handle_LTC6804_PEC(ERROR_STATUS_T* er_stat, uint32_t msTicks) {
	if (er_stat->error == false) {
		er_stat->handling = false;
		return HANDLER_FINE;
	} else {
		//[TODO] magic numbers changeme 
		if (er_stat->count < 50) {
			er_stat->handling = true;
			return HANDLER_FINE
		} else {
			return HANDLER_HALT
		}
	}
}
ERROR_HANDLER_STATUS_T handle_ERROR(ERROR_STATUS_T* er_stat, uint32_t msTicks) {
	return HANDLER_HALT;
}
ERROR_HANDLER_STATUS_T handle_INVALID_SSM_STATE(ERROR_STATUS_T* er_stat, uint32_t msTicks) {
	return HANDLER_HALT;
}
ERROR_HANDLER_STATUS_T handle_CONTACTORS_ERRONEOUS_STATE(ERROR_STATUS_T* er_stat, uint32_t msTicks) {
	return HANDLER_HALT;
}
ERROR_HANDLER_STATUS_T handle_CELL_UNDER_VOLTAGE(ERROR_STATUS_T* er_stat, uint32_t msTicks) {
	if (er_stat->error == false) {
		er_stat->handling = false;
		return HANDLER_FINE;
	} else {
		//[TODO] magic numbers changem
		if (msTicks - er_stat->time_stamp < 1000) {
			er_stat->handling = true;
			return HANDLER_FINE;
		} else {
			return HANDLER_HALT;
		}
	}
}
ERROR_HANDLER_STATUS_T handle_CELL_OVER_VOLTAGE(ERROR_STATUS_T* er_stat, uint32_t msTicks) {
	return HANDLER_HALT;
}
ERROR_HANDLER_STATUS_T handle_CELL_OVER_TEMP(ERROR_STATUS_T* er_stat, uint32_t msTicks) {
	if (er_stat->error == false) {
		er_stat->handling = false;
		return HANDLER_FINE;
	} else {
		//[TODO] magic numbers changem
		if (msTicks - er_stat->time_stamp < 1000) {
			er_stat->handling = true;
			return HANDLER_FINE;
		} else {
			return HANDLER_HALT;
		}
	}
}
ERROR_HANDLER_STATUS_T handle_OVER_CURRENT(ERROR_STATUS_T* er_stat, uint32_t msTicks) {
	if (er_stat->error == false) {
		er_stat->handling = false;
		return HANDLER_FINE;
	} else {
		//[TODO] magic numbers changem
		if (msTicks - er_stat->time_stamp < 1000) {
			er_stat->handling = true;
			return HANDLER_FINE;
		} else {
			return HANDLER_HALT;
		}
	}
}