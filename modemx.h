#pragma once
#include <vector>
#include <string>

std::vector<std::string> splitstring(std::string line, char limiter);
int seatsort(std::string line, char c, int maxpos);
std::string getClipboard();
bool ValidateIp(std::string ipstring);
void pingIp(std::string ip);