bool Pipeline::hasDependency(void) {

	if(pipeline[DECODE].inst->type == NOP)
		return false;

	// Checks if dependency exist between Decode stage and Exec, Mem stage
	// We assume the register file can read/write in the same cycle so no data dependency exist with RAW dependency if an instruction is in Decode and WB.
	for(int i = EXEC; i < WB; i++) {

		if( pipeline[i].inst == NULL )
			continue;		

		if( pipeline[i].inst->type == NOP )
			continue;

		if( (pipeline[i].inst->dest != -1) && 
		    (pipeline[i].inst->dest == pipeline[DECODE].inst->src1 ||
		     pipeline[i].inst->dest == pipeline[DECODE].inst->src2) ) {
			//EXEC/MEM-->DECODE
			if (i - DECODE <= 2) {
				if (i == 2 && pipeline[i].inst->type == LW)
					return true;
				else
					return false;
			}
			//MEM/WB-->DECODE
			if (i - DECODE == 3 || i - DECODE == 2)
				return false;
		}

	}

	
	return false;

}
