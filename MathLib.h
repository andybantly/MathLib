#pragma once
#include <vector>
#include <string>
#include <mutex>

std::mutex g_io_mutex;

static void ttest(unsigned long long ullb, unsigned long long ulle);
static void test();
void Split(const std::string& strInput, std::vector<std::string>& vstrTokens, const char cFind);


