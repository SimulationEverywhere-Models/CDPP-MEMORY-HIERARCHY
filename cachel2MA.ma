[top]
components : cachel2@CacheL2 
in : AddressIn
in : DataIn
out : AddressOut
out : DataOut
out : ErrorOut

Link : AddressIn AddressIn@cachel2
Link : DataIn DataIn@cachel2
Link : AddressOut@cachel2 AddressOut
Link : DataOut@cachel2 DataOut
Link : ErrorOut@cachel2 ErrorOut

[cachel2]
CacheAccessTime : 00:00:10:000
CacheTimingOutTime : 00:00:50:000