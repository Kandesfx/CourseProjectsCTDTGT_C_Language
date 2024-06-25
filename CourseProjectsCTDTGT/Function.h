#ifndef _Function_h
#define _Function_h

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "CampaignSList.h"
#include "VolunteerSList.h"
#include "CheckingFunction.h"

void ReadFile_CP(FILE* fcp, Campaign& cp); //Đọc theo thông tin chiến dịch định dạng
int inputCampaignList_LoadFile(CampaignSList& lcp); //Khởi tạo danh sách có dự liệu từ file chiendich.txt
void ReadFile_VT(FILE* fcp, Volunteer& vt); //Đọc thông tin tình nguyện viên theo định dạng
int inputVolunteerList_LoadFile(CampaignSList lcp, VolunteerSList& lvt); //Khởi tạo danh sách có dự liệu từ file tinhnguyenvien.txt
int addVolunteer(VolunteerSList& lvt, CampaignSList lcp);// Thêm tình nguyện viên mới vào danh sách
CampaignSNode* findVolunteerBytenCD(CampaignSList lcp, VolunteerSList lvt, char tenCD[]); //Tìm kiếm tình nguyện viên theo tên chiến dịch
VolunteerSNode* findVolunteerByMaTNV(VolunteerSList lvt, char maTNV[]); //Tìm kiếm tình nguyện viên theo mã tình nguyện viên
VolunteerSNode* findVolunteerBySDT(VolunteerSList lvt, char SDT[]); //Tìm kiếm tình nguyện viên thoe số điện thoại
void showVLTByCP(CampaignSNode* cp, VolunteerSList lvt); //Hiện thị tình nguyện viên thuộc chiến dịch
void searchVolunteer(CampaignSList lcp, VolunteerSList lvt); //Tìm kiếm tình nguyện viên theo các tiêu chí
void showFullVolunteerByCP(CampaignSList lcp, VolunteerSList lvt); //Hiển thị toàn bộ danh sách tình nguyện viên theo chiến dịch
VolunteerSNode* findMaxYear(VolunteerSList lvt); //Tìm năm sinh lớn nhất trong danh sách
void showVolunteerMinAge(VolunteerSList lvt); //Hiển thị danh sách tình nguyện viên có tuổi nhỏ nhất
void findVolunteersMostday(CampaignSList lcp, VolunteerSList lvt); //Tìm kiếm các tình nguyện viên tham gia chiến dịch dài ngày nhất
void swapVLT(Volunteer& x, Volunteer& y); //Hoán đổi thông tông tin của 2 nút
void sortVolunteers_ByNameCP(CampaignSList lcp, VolunteerSList& lvt); //Sắp xếp tình nguyện viên theo mã chiến dịch và giảm dần theo tuổi của tình nguyện viên
void VolunteersSortAgeDecreaseName(VolunteerSList lvt); //Hiển thị danh sách tình nguyện viên có tuổi <20 và giảm dần theo tên
void writeLog(char feildUpdate[], char InfoBefore[], char InfoAfter[], VolunteerSNode* p); //Ghi vào file log.txt thông tin vừa cập nhật
void updateInfomation(VolunteerSNode*& p, CampaignSList lcp, VolunteerSList lvt); //Cập nhật thông tin tình nguyện viên
void updateVLTandWriteLog(CampaignSList lcp, VolunteerSList lvt); //Cập nhật thông tin và ghi lại cập nhật

#endif _Function_h