[top]
components : centralprocessingunit@CentralProcessingUnit 
out : AddressOut
out : DataReceived
out : ErrorOut
in : ControlIn
in : DataIn


Link : ControlIn ControlIn@centralprocessingunit
Link : DataIn DataIn@centralprocessingunit
Link : DataReceived@centralprocessingunit DataReceived
Link : AddressOut@centralprocessingunit AddressOut
Link : ErrorOut@centralprocessingunit ErrorOut

[centralprocessingunit]
distribution : normal
mean : 3
deviation : 1
