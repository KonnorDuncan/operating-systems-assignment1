# operating-systems-assignment1

The program compiles and runs with incorrect behavior. Every time I have tested, the producer creates an 83, an 86, then the program hangs for a while before ending. The program was compiled and ran in an WSL Ubuntu instance with:
$ gcc producer.c -pthread -lrt -o producer
$ gcc consumer.c -pthread -lrt -o consumer
$ ./producer & ./consumer &


![image](https://github.com/KonnorDuncan/operating-systems-assignment1/assets/166071552/eef646a5-98b1-4c9c-b325-a689e24c29c7)
