#ifndef _CheckingFunction_h
#define _CheckingFunction_h

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "CampaignSList.h"
#include "VolunteerSList.h"

int isEmpty_lcp(CampaignSList lcp); //Kiểm tra danh sách chiến dịch rỗng
int isEmpty_lvt(VolunteerSList lvt); //Kiểm tra danh sách tình nguyện viên rỗng
int checkSDT(VolunteerSList lvt, Volunteer vt); //Kiểm tra tồn tại số điện thoại có trong danh sách
int checkMaTNV(VolunteerSList lvt, Volunteer vt); //Kiểm tra tồn tại mã tình nguyện viên trong danh sách
int checkMaCP(CampaignSList lcp, Volunteer vt); //Kiểm tra tồn tại mã chiến dịch trong danh sách
int checkSDTFormat(char* SDT); //Kiểm tra của định dạng số điện thoại nhập vào
int checkBrtDayFormat(char* BrtDay); //Kiểm tra định dạng ngày tháng năm nhập vào
#endif _CheckingFunction_h