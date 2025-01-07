

#ifndef PID_TESTYPID_H
#define PID_TESTYPID_H

#include <vector>

void raportBleduSekwencji(std::vector<double>& spodz, std::vector<double>& fakt);
bool porownanieSekwencji(std::vector<double>& spodz, std::vector<double>& fakt);
void test_RegulatorP_brakPobudzenia();
void test_RegulatorP_skokJednostkowy();
void test_RegulatorPI_skokJednostkowy_1();
void test_RegulatorPI_skokJednostkowy_2();
void test_RegulatorPID_skokJednostkowy();





#endif //PID_TESTYPID_H
