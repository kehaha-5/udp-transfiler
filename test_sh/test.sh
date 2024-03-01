 
 #内存使用测试
 valgrind --tool=massif --time-unit=B --detailed-freq=1 --massif-out-file=./valgrindCheck/massif.out.server ./build/TRANFILER_SERVER
 valgrind --tool=massif --time-unit=B --detailed-freq=1 --massif-out-file=./valgrindCheck/massif.out.client ./build/TRANFILER_CLIENT
 #查看测试结果
 massif-visualizer ./valgrindCheck/massif.out.server
 massif-visualizer ./valgrindCheck/massif.out.client

 #内存泄漏测试
 valgrind --leak-check=full --show-leak-kinds=all   --trace-children=yes --log-file=./valgrindCheck/val_log_client.log ./build/TRANFILER_CLIENT
 valgrind --leak-check=full --show-leak-kinds=all   --trace-children=yes --log-file=./valgrindCheck/val_log_ser.log ./build/TRANFILER_SERVER

 #CPU性能检测
 valgrind --tool=callgrind --separate-threads=yes ./build/TRANFILER_CLIENT
 valgrind --tool=callgrind --separate-threads=yes ./build/TRANFILER_SERVER
 #查看结果
 sudo kcachegrind