When threads access and write to variable "counter" at the same time, race conditional happens, so the actual counter when this program finishes is less than expected counter. Using mutex help to ensure that at a time there is only one thread is writing to "counter".
    
