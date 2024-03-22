```
> make run b=release
g++-13 -std=c++23  -O3 main.cpp -o main 
./main
'c_is_ascii             (10, 100000)': processed 976 kb in 2.21 ms at 430.82 mb/s
'is_acsii_bit           (10, 100000)': processed 976 kb in 454.66 us at 2.05 gb/s
'is_ascii_bit_chunked   (10, 100000)': processed 976 kb in 272.77 us at 3.41 gb/s
'is_ascii_bit_intrinsics(10, 100000)': processed 976 kb in 545.56 us at 1.71 gb/s

'c_is_ascii             (25, 100000)': processed 2 mb in 5.45 ms at 437.30 mb/s
'is_acsii_bit           (25, 100000)': processed 2 mb in 1.29 ms at 1.81 gb/s
'is_ascii_bit_chunked   (25, 100000)': processed 2 mb in 348.29 us at 6.68 gb/s
'is_ascii_bit_intrinsics(25, 100000)': processed 2 mb in 581.59 us at 4.00 gb/s

'c_is_ascii             (50, 100000)': processed 4 mb in 10.58 ms at 450.65 mb/s
'is_acsii_bit           (50, 100000)': processed 4 mb in 1.43 ms at 3.25 gb/s
'is_ascii_bit_chunked   (50, 100000)': processed 4 mb in 1.14 ms at 4.08 gb/s
'is_ascii_bit_intrinsics(50, 100000)': processed 4 mb in 437.60 us at 10.64 gb/s

'c_is_ascii             (100, 100000)': processed 9 mb in 22.65 ms at 421.03 mb/s
'is_acsii_bit           (100, 100000)': processed 9 mb in 3.68 ms at 2.53 gb/s
'is_ascii_bit_chunked   (100, 100000)': processed 9 mb in 1.52 ms at 6.14 gb/s
'is_ascii_bit_intrinsics(100, 100000)': processed 9 mb in 546.14 us at 17.05 gb/s

'c_is_ascii             (200, 100000)': processed 19 mb in 41.54 ms at 459.20 mb/s
'is_acsii_bit           (200, 100000)': processed 19 mb in 7.02 ms at 2.65 gb/s
'is_ascii_bit_chunked   (200, 100000)': processed 19 mb in 2.76 ms at 6.75 gb/s
'is_ascii_bit_intrinsics(200, 100000)': processed 19 mb in 799.80 us at 23.29 gb/s

'c_is_ascii             (300, 100000)': processed 28 mb in 62.42 ms at 458.34 mb/s
'is_acsii_bit           (300, 100000)': processed 28 mb in 7.56 ms at 3.69 gb/s
'is_ascii_bit_chunked   (300, 100000)': processed 28 mb in 4.21 ms at 6.64 gb/s
'is_ascii_bit_intrinsics(300, 100000)': processed 28 mb in 1.06 ms at 26.38 gb/s

'c_is_ascii             (104857600, 1)': processed 100 mb in 211.67 ms at 472.43 mb/s
'is_acsii_bit           (104857600, 1)': processed 100 mb in 23.83 ms at 4.10 gb/s
'is_ascii_bit_chunked   (104857600, 1)': processed 100 mb in 15.41 ms at 6.34 gb/s
'is_ascii_bit_intrinsics(104857600, 1)': processed 100 mb in 3.84 ms at 25.40 gb/s
```
