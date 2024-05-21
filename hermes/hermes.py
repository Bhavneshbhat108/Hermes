import ctypes
import numpy as np

class Buffer(ctypes.Structure):
    _fields_ = [
        ("data", ctypes.c_ubyte * (32 * 512 * 4096 * 16))  # BLKSIZE * MAXBLKS
    ]
# Maximum Amount of Data

lib = ctypes.CDLL('./libhermes.so')

lib.get_raw_data.argtypes = [ctypes.c_int, ctypes.c_int]
lib.get_raw_data.restype = ctypes.POINTER(ctypes.c_ubyte)

lib.free_raw_data.argtypes = [ctypes.POINTER(ctypes.c_ubyte)]
lib.free_raw_data.restype = None
def Eris(n1,n2,dump):
    block_size = ctypes.c_int()
    raw_ptr = lib.get_raw_data(n1, n2, ctypes.byref(block_size))

    if raw_ptr:
       raw_data = np.ctypeslib.as_array(raw_ptr, shape=(block_size.value // 4096, 4096))
       lib.free_raw_data(raw_ptr)
       if (dump == 1):
           filename="Tcand_"+str(21.47*n1)+"_.npy"
           np.save(filename, raw_data_array)
       return raw_data

    else :
      raise ValueError("Failed to retrieve raw data.")
