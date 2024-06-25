#include "Function.h"

void ReadFile_CP(FILE* fcp, Campaign& cp)
{
	fscanf_s(fcp, "%[^#]#%[^#]#%[^#]#%s\n", cp.maCD, sizeof(cp.maCD), cp.tenCD, sizeof(cp.tenCD), cp.ngayBD, sizeof(cp.ngayBD), cp.ngayKT, sizeof(cp.ngayKT));
	/* %[^#]: Đọc vào chuỗi ký tự cho tới trước '#'
	   #: Đọc vào dấu '#' để loại bỏ đi chính nó
	   %s: đọc chuỗi ký tự cho tới cuối */
}
int inputCampaignList_LoadFile(CampaignSList& lcp)
{
	Campaign cp;
	FILE* fcp;
	fopen_s(&fcp, "chiendich.txt", "rt");
	if (fcp == NULL)
	{
		printf_s("\nLoi doc file");
		return 0; //Mở file không thành công
	}
	int n;
	fscanf_s(fcp, "%d\n", &n); //Đọc vào số phần tử có trong file
	for (int i = 0; i < n; i++)
	{
		//Với mỗi dòng đọc theo định dạng và lưu thông tin của tình nguyện viên
		ReadFile_CP(fcp, cp);
		CampaignSNode* newNode = CreateCampaignSNode(cp);
		insertTail_lcp(lcp, newNode); //Lưu tình nguyện viên vào cuối danh sách
	}
	fclose(fcp);
	return 1; //Đọc file thành công
}
void ReadFile_VT(FILE* fcp, Volunteer& vt)
{
	fscanf_s(fcp, "%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%s\n", vt.maTNV, sizeof(vt.maTNV), vt.Ho, sizeof(vt.Ho), vt.Ten, sizeof(vt.Ten), vt.brtDay, sizeof(vt.brtDay), vt.SDT, sizeof(vt.SDT), vt.MaCD, sizeof(vt.MaCD));
	/* %[^#]: Đọc vào chuỗi ký tự cho tới trước '#'
	   #: Đọc vào dấu '#' để loại bỏ đi chính nó
	   %s: đọc chuỗi ký tự cho tới cuối */
}
int inputVolunteerList_LoadFile(CampaignSList lcp, VolunteerSList& lvt)
{
	if (isEmpty_lcp(lcp) == 1)
	{
		printf_s("\nDanh sach chien dich rong! Khong the doc file.");
		return 0; //Hàm chỉ thực hiện khi danh sách chiến dịch tồn tại
	}
	Volunteer vt;
	FILE* fvt;
	fopen_s(&fvt, "tinhnguyenvien.txt", "rt");
	if (fvt == NULL)
	{
		printf_s("\nLoi doc file");

		return 0; //Mở file không thành công
	}
	int n;
	fscanf_s(fvt, "%d\n", &n); //Đọc vào số phần tử có trong file
	for (int i = 0; i < n; i++)
	{
		//Với mỗi dòng đọc theo định dạng và lưu thông tin của tình nguyện viên
		ReadFile_VT(fvt, vt);
		//Kiểm tra mã chiến dịch của tình nguyện viên vừa đọc được có hợp lệ tồn tại trong danh sách chiến dịch
		if (checkMaCP(lcp, vt) == 1) //Nếu tồn tại thì thêm tình nguyện viên vào danh sách
		{
			VolunteerSNode* newNode = CreateVolunteerSNode(vt);
			insertTail_lvt(lvt, newNode);
		}
		else //Nếu không tồn tại thì báo lỗi và không thêm
		{
			printf_s("\nTinh nguyen vien %s co ma chien dich %s khong hop le! Du lieu tinh nguyen vien nay se bi bo qua!", vt.maTNV, vt.MaCD);
		}
	}
	fclose(fvt);
	return 1; //Đọc file thành công
}
int addVolunteer(VolunteerSList& lvt, CampaignSList lcp)
{
	int result, prm;
	if (isEmpty_lcp(lcp) == 1)
	{
		printf_s("\nDanh sach chien dich dang rong! Thuc hien chuc nang khong thanh cong...");
		return 0; //Hàm chỉ thực hiện khi danh sách chiến dịch tồn tại
	}
	Volunteer p;
	getchar();
	do
	{
		//Người dùng nhập vào thông tin mã tình nguyện viên, nếu đã tồn tại phải nhập lại
		printf_s("\nNhap ma tinh nguyen vien: ");
		gets_s(p.maTNV, 13);
		result = checkMaTNV(lvt, p);
		if (result == 1)
		{
			printf_s("\nMa tinh nguyen vien da ton tai! Moi nhap ma khac\n");
		}
	} while (result != 0); 
	printf_s("\nNhap ho: ");
	gets_s(p.Ho, 23);
	printf_s("\nNhap ten: ");
	gets_s(p.Ten, 9);
	do
	{
		//Nhập ngày tháng năm sinh tình nguyện viên, nếu sai định dạng hoặc thời gian không hợp lệ phải nhập lại
		printf_s("\nNhap ngay thang nam sinh (So tuoi > 14, VD: 11/02/2005): ");
		gets_s(p.brtDay, 23);
		result = checkBrtDayFormat(p.brtDay);
		if (result == 0)
		{
			printf_s("\nDinh dang hoac thoi gian ban nhap vao khong dung! Moi nhap lai...\n");
		}
	} while (result != 1);
	do
	{
		printf_s("\nNhap so dien thoai: ");
		gets_s(p.SDT, 23);
		result = checkSDTFormat(p.SDT);
		if (result == 0)
		{
			printf_s("\nDinh dang ban nhap vao khong dung! Moi nhap lai...\n");
			continue; //Định dạng không hợp lệ thì nhập lại
		}
		prm = checkSDT(lvt, p); //Kiểm tra số điện thoại đã tồn tại trong chiến dịch
		if (prm == 1)
		{
			printf_s("\nSo dien thoai nay da ton tai! Moi nhap lai...");
			result = 0; //Nếu trùng với số đã có trong chiến dịch thì phải nhập lại
		}
		else
		{
			result = 1; //Nếu không trùng thì bỏ qua
		}
	} while (result != 1);
	printf_s("\nNhap ma chien dich tinh nguyen vien tham gia: ");
	gets_s(p.MaCD, 11);
	if (checkMaCP(lcp, p) == 1) //Tồn tại mã chiến dịch thì mới thêm tình nguyên viên vào danh sách
	{
		VolunteerSNode* newNode = CreateVolunteerSNode(p);
		insertTail_lvt(lvt, newNode);
		return 1; //Thêm tình nguyện viên thành công
	}
	else //Nếu mã chiến dịch không đúng thì huỷ chức năng và thoát ra ngoài menu
	{
		printf_s("\n Ma chien dich khong hop le! Khong the them...\n");
		return 0;
	}
}
CampaignSNode* findVolunteerBytenCD(CampaignSList lcp, VolunteerSList lvt, char tenCD[])
{
	CampaignSNode* p = lcp.head;
	while (p != NULL)
	{
		if (strcmp(p->info.tenCD, tenCD) == 0)
			return p; //Trả về kết quả nếu tìm thấy
		p = p->next;
	}
	return NULL; //Trả về rỗng nếu không tồn tại
}
VolunteerSNode* findVolunteerByMaTNV(VolunteerSList lvt, char maTNV[])
{
	VolunteerSNode* p = lvt.head;
	while (p != NULL)
	{
		if (strcmp(p->info.maTNV, maTNV) == 0)
			return p; //Trả về kết quả nếu tìm thấy
		p = p->next;
	}
	return NULL; //Trả về rỗng nếu không tồn tại
}
VolunteerSNode* findVolunteerBySDT(VolunteerSList lvt, char SDT[])
{
	VolunteerSNode* p = lvt.head;
	while (p != NULL)
	{
		if (strcmp(p->info.SDT, SDT) == 0)
			return p; //Trả về kết quả nếu tìm thấy
		p = p->next;
	}
	return NULL; //Trả về rỗng nếu không tồn tại
}
void showVLTByCP(CampaignSNode* cp, VolunteerSList lvt)
{
	int t = 0;
	for (VolunteerSNode* p = lvt.head; p != NULL; p = p->next)
	{
		if (strcmp(p->info.MaCD, cp->info.maCD) == 0)
		{
			showVolunteerSNode(p); //Hiển thị những tình nguyện viên có mã chiến dịch trùng
			t = 1;
		}
	}
	if (t == 0)
	{
		printf_s("Chien dich nay hien khong co thanh vien!");
	}
}
void searchVolunteer(CampaignSList lcp, VolunteerSList lvt)
{
	if (isEmpty_lvt(lvt) == 1)
	{
		printf_s("\nDanh sach tinh nguyen vien rong! Khong the tim kiem..."); 
		return; //Hàm chỉ thực hiện khi tồn tại danh sách tình nguyện viên
	}
	int choice;
	char keyword[20];
	CampaignSNode* resultTenCD;
	VolunteerSNode* resultTNV;
	printf_s("\n\n\tChon tieu chi tim kiem:");
	printf_s("\n\t1. Ten chien dich");
	printf_s("\n\t2. Ma tinh nguyen vien");
	printf_s("\n\t3. So dien thoai tinh nguyen vien");
	printf_s("\nNhap lua chon cua ban: ");
	scanf_s("%d", &choice);
	getchar();
	switch (choice)
	{
	case 1:
		printf_s("\nNhap ten chien dich can tim: ");
		gets_s(keyword);
		resultTenCD = findVolunteerBytenCD(lcp, lvt, keyword);
		if (resultTenCD != NULL)
			showVLTByCP(resultTenCD, lvt); //Nếu tồn tại chiến dịch thì hiển thị toàn bộ thành viên
		else
			printf_s("\nKhong ton tai chien dich co ten '%s'", keyword);
		break;
	case 2:
		printf_s("\nNhap ma tinh nguyen vien can tim: ");
		gets_s(keyword);
		resultTNV = findVolunteerByMaTNV(lvt, keyword);
		if (resultTNV != NULL)
			showVolunteerSNode(resultTNV); //Hiển thị tình nguyện viên nếu có tồn tại mã trong danh sách
		else
			printf_s("\nKhong tim thay tinh nguyen vien theo maTNV '%s'", keyword);
		break;
	case 3:
		printf_s("\nNhap so dien thoai can tim: ");
		gets_s(keyword);
		resultTNV = findVolunteerBySDT(lvt, keyword);
		if (resultTNV != NULL)
			showVolunteerSNode(resultTNV); //Hiển thị tình nguyện viên nếu có tồn tại số điên thoại trong danh sách
		else
			printf_s("\nKhong tim thay tinh nguyen vien theo SDT '%s'", keyword);
		break;
	default:
		printf_s("\nLua chon khong hop le!");
		break;
	}
}
void showFullVolunteerByCP(CampaignSList lcp, VolunteerSList lvt)
{
	if (isEmpty_lvt(lvt) == 1)
	{
		printf_s("\nDanh sach tinh nguyen vien rong! Khong the tim kiem...");
		return; //Hàm chỉ thực hiện khi tồn tại danh sách tình nguyện viên
	}
	for (CampaignSNode* p = lcp.head; p != NULL; p = p->next)
	{
		printf_s("\n   Chien dich:\t%s\n", p->info.tenCD);
		showVLTByCP(p, lvt); //Hiển thị những tình nguyện viên có mã chiến dịch hợp lệ
	}
}
VolunteerSNode* findMaxYear(VolunteerSList lvt)
{
	if (isEmpty_lvt(lvt) == 1)
	{
		return NULL; //Hàm chỉ thực hiện khi tồn tại danh sách tình nguyện viên
	}
	int day, month, year;
	VolunteerSNode* yearMax = lvt.head;
	sscanf_s(yearMax->info.brtDay, "%d/%d/%d", &day, &month, &year); //Đọc ngày tháng năm để xủ lý

	//Lấy thời gian hiện tại
	time_t now = time(NULL); 
	struct tm localTime;
	localtime_s(&localTime, &now);
	int currentYear = localTime.tm_year + 1900; //Năm hiện tại

	int ageMaxSet = currentYear - year; //Khởi tạo năm lớn nhất
	//Tìm kiếm năm lớn nhất
	for (VolunteerSNode* p = lvt.head; p != NULL; p = p->next)
	{
		sscanf_s(p->info.brtDay, "%d/%d/%d", &day, &month, &year); //Đọc định dạng dữ liệu từ ký tự ngày sinh
		int age = currentYear - year;
		if (age < ageMaxSet) //Tìm tuổi nhỏ nhất thì nó có số năm lớn nhất
		{
			yearMax = p;
		}
	}
	return yearMax; //Trả về kết quả con trỏ năm lớn nhất
}
void showVolunteerMinAge(VolunteerSList lvt)
{
	if (isEmpty_lvt(lvt) == 1)
	{
		printf_s("\nDanh sach tinh nguyen vien rong!");
		return; //Hàm chỉ thực hiện khi tồn tại danh sách tình nguyện viên
	}
	int day, month, year, yearMax;
	VolunteerSNode* q = findMaxYear(lvt); //Con trỏ nút có số tuổi nhỏ nhất
	sscanf_s(q->info.brtDay, "%d/%d/%d", &day, &month, &yearMax);
	//Hiển thị các thành viên có tuổi nhỏ nhất
	printf_s("\n\tDanh sach tinh nguyen vien co tuoi nho nhat la: \n");
	for (VolunteerSNode* p = lvt.head; p != NULL; p = p->next)
	{
		sscanf_s(p->info.brtDay, "%d/%d/%d", &day, &month, &year);
		if (year == yearMax)
		{
			showVolunteerSNode(p);
		}
	}
}
void findVolunteersMostday(CampaignSList lcp, VolunteerSList lvt) 
{
	if (isEmpty_lvt(lvt) == 1)
	{
		printf_s("\nDanh sach tinh nguyen vien rong!");
		return; //Hàm chỉ thực hiện khi tồn tại danh sách tình nguyện viên
	}
	int maxDay = 0;
	int ngayBD, thangBD, namBD, ngayKT, thangKT, namKT;
	for (CampaignSNode* p = lcp.head; p != NULL; p = p->next) //Duyệt danh sách
	{
		int ngayBD, thangBD, namBD;
		int ngayKT, thangKT, namKT;
		sscanf_s(p->info.ngayBD, "%d/%d/%d", &ngayBD, &thangBD, &namBD); //Đọc định dạng dữ liệu từ ký tự thời gian bắt đầu
		sscanf_s(p->info.ngayKT, "%d/%d/%d", &ngayKT, &thangKT, &namKT); //Đọc định dạng dữ liệu từ ký tự thời gian kết thúc
		int day = (namKT - namBD) * 365 + (thangKT - thangBD) * 30 + (ngayKT - ngayBD); // Chuyển thành ngày
		if (day > maxDay)
		{
			maxDay = day; //Tìm chiến dịch có thời dài nhất 
		}
	}
	printf_s("\nThong tin cac tinh nguyen vien tham gia chien dich co thoi gian dien ra %d ngay: ", maxDay);
	for (CampaignSNode* p = lcp.head; p != NULL; p = p->next) //Duyệt danh sách chiến dịch
	{
		int ngayBD, thangBD, namBD;
		int ngayKT, thangKT, namKT;
		sscanf_s(p->info.ngayBD, "%d/%d/%d", &ngayBD, &thangBD, &namBD); //Đọc định dạng dữ liệu từ ký tự thời gian bắt đầu
		sscanf_s(p->info.ngayKT, "%d/%d/%d", &ngayKT, &thangKT, &namKT); //Đọc định dạng dữ liệu từ ký tự thời gian kết thúc
		int day = (namKT - namBD) * 365 + (thangKT - thangBD) * 30 + (ngayKT - ngayBD); // Chuyển thành ngày
		if (day == maxDay) 
		{
			printf("\n\tChien dich: %s\n", p->info.tenCD);
			showVLTByCP(p, lvt); //Nếu tồn tại những chiến dịch có thơi gian tương tự thì hiển thị những thành viên thuôc jchieens dịch đó
		}
	}
}
void swapVLT(Volunteer& x, Volunteer& y)
{
	Volunteer tmp;
	tmp = x;
	x = y;
	y = tmp;
}
void sortVolunteers_ByNameCP(CampaignSList lcp, VolunteerSList& lvt)
{
	if (isEmpty_lvt(lvt) == 1)
	{
		return; //Hàm chỉ thực hiện khi tồn tại danh sách tình nguyện viên
	}
	int ngay1, thang1, nam1, ngay2, thang2, nam2;
	VolunteerSList tempVolunteerList;
	InitVolunteerSList(tempVolunteerList); //Khởi tạo danh sách tạm thời rỗng
	//Sắp xếp các tình nguyện viên có cùng mã chiến dịch ở cạnh nhau
	for (CampaignSNode* p = lcp.head; p != NULL; p = p->next)
	{
		for (VolunteerSNode* q = lvt.head; q != NULL; q = q->next)
		{
			if (strcmp(q->info.MaCD, p->info.maCD) == 0)
			{
				VolunteerSNode* newNode = CreateVolunteerSNode(q->info);
				insertTail_lvt(tempVolunteerList, newNode); //Thêm vào danh sách tạm thời
			}
		}
	}
	
	deleteVLTSList(lvt); //Giải phóng các phần tử trong danh sách chính
	lvt = tempVolunteerList; //Gán danh sách tạm thời cho danh saqchs chính
	deleteVLTSList(tempVolunteerList); //Giải phóng bộ nhớ trong danh sách tạm thời

	//Sắp xếp lại các tình nguyện viên có cùng mã giảm dần theo tuổi
	for (VolunteerSNode* p = lvt.head; p != NULL; p = p->next)
	{
		for (VolunteerSNode* q = p->next; q != NULL; q = q->next)
		{
			if (strcmp(q->info.MaCD, p->info.MaCD) == 0)
			{
				sscanf_s(p->info.brtDay, "%d/%d/%d", &ngay1, &thang1, &nam1); //Đọc định dạng dữ liệu từ ký tự ngày sinh
				sscanf_s(q->info.brtDay, "%d/%d/%d", &ngay2, &thang2, &nam2); //Đọc định dạng dữ liệu từ ký tự ngày sinh phần tử liền kề
				if (nam1 > nam2 || (nam1 == nam2 && thang1 > thang2) || (nam1 == nam2 && thang1 == thang2 && ngay1 > ngay2))
				{
					swapVLT(p->info, q->info); //Hoán đổi thông tin nếu người thứ nhất có thời gian sinh sau người thứ 2
				}
			}
			else
			{
				break;
			}

		}
	}
}
void VolunteersSortAgeDecreaseName(VolunteerSList lvt)
{
	if (isEmpty_lvt(lvt) == 1)
	{
		printf_s("\nDanh sach tinh nguyen vien rong!");
		return;
	}
	int ngay, thang, nam, tuoi;

	//Khởi tạo danh sách tạm thời
	VolunteerSList lvt_tmp;
	InitVolunteerSList(lvt_tmp);

	//Lấy dữ liệu thời gian hiện tại
	struct tm localTime;
	time_t now = time(NULL);
	localtime_s(&localTime, &now);
	int currentTimetoDay = (localTime.tm_year + 1900) * 365 + (localTime.tm_mon + 1) * 30 + localTime.tm_mday; //Chuyển đổi ra ngày

	//Loc tinh nguyen vien co tuoi < 20;
	for (VolunteerSNode* p = lvt.head; p != NULL; p = p->next)
	{
		sscanf_s(p->info.brtDay, "%d/%d/%d", &ngay, &thang, &nam);
		int chageToDay = nam * 365 + thang * 30 + ngay; //Đổi thành ngày
		tuoi = (currentTimetoDay - chageToDay) / 365; //Độ tuổi
		if (tuoi < 20)
		{
			VolunteerSNode* newNode = CreateVolunteerSNode(p->info);
			insertTail_lvt(lvt_tmp, newNode); //Nếu tuổi của tình nguyên viên bé hơn 20 thì thêm vào danh sách tạm thời
		}
	}

	//Sắp xếp lại giảm dần theo tên
	for (VolunteerSNode* p = lvt_tmp.head; p != NULL; p = p->next)
	{
		for (VolunteerSNode* q = p->next; q != NULL; q = q->next)
		{
			if (strcmp(p->info.Ten,q->info.Ten) > 0)
			{
				swapVLT(p->info, q->info);
			}
		}
	}
	showVolunteerSList(lvt_tmp); //Hiển thị danh sách sau khi sắp xếp
	deleteVLTSList(lvt_tmp); //Giai phong bo nho
}
void writeLog(char feildUpdate[], char InfoBefore[], char InfoAfter[], VolunteerSNode* p)
{
	char InfoNow[20];
	FILE* log;

	fopen_s(&log, "log.txt", "a");
	if (!log)
	{
		printf_s("\nLoi mo File!\n");
		return; //Mở file không thành công
	}

	//Lây thời gian hiện tại
	time_t now;
	struct tm localTime;
	time(&now);
	localtime_s(&localTime, &now);

	strftime(InfoNow, sizeof(InfoNow), "%d/%m/%Y %H:%M", &localTime); //Định dạng thời gian thành chỗi ký tự
	fprintf_s(log, "%s || ID: %s || Thuoc tinh cap nhat: %s || %s -> %s\n", InfoNow, p->info.maTNV, feildUpdate, InfoBefore, InfoAfter); //Ghi vào file
	fclose(log);
	printf_s("\nDa cap nhat file log\n");
}
void updateInfomation(VolunteerSNode*& p, CampaignSList lcp, VolunteerSList lvt)
{
	Volunteer x;
	int luachon, result;
	char getInfoBefore[25], getInfoAfter[25], feildUpdate[25];
	do
	{
		printf_s("\nChon truong thong tim muon cap nhat: ");
		printf_s("\n1. Thay doi ho, ten tinh nguyen vien");
		printf_s("\n2. Thay doi ngay thang nam sinh tinh nguyen vien");
		printf_s("\n3. Thay doi so dien thoai tinh nguyen vien");
		printf_s("\n4. Thay doi ma chien dich tinh nguyen vien");
		printf_s("\nNhap lua chon cua ban: ");
		scanf_s("%d", &luachon);
		getchar();
		switch (luachon)
		{
		case 1:
			strcpy_s(getInfoBefore, p->info.Ho); //Lấy thông tin trước khi thay đổi
			printf_s("\nNhap ho tinh nguyen vien: ");
			gets_s(x.Ho, 23);
			strcpy_s(p->info.Ho, x.Ho); //Cập nhật thông tin
			strcpy_s(getInfoAfter, p->info.Ho); //Lấy thông tin sau khi thay đổi
			strcpy_s(feildUpdate, "Ho"); //Trường thông tin bị thay đổi
			writeLog(feildUpdate, getInfoBefore, getInfoAfter, p); //Ghi lại những thông tin trên vào file log
			//-------------------------------------------------------------------------------------------------
			strcpy_s(getInfoBefore, p->info.Ten); //Lấy thông tin trước khi thay đổi
			printf_s("\nNhap ten tinh nguyen vien: ");
			gets_s(x.Ten, 9);
			strcpy_s(p->info.Ten, x.Ten); //Cập nhật thông tin
			strcpy_s(getInfoAfter, p->info.Ten); //Lấy thông tin sau khi thay đổi
			strcpy_s(feildUpdate, "Ten"); //Trường thông tin bị thay đổi
			writeLog(feildUpdate, getInfoBefore, getInfoAfter, p); //Ghi lại những thông tin trên vào file log
			break;
		case 2:
			strcpy_s(getInfoBefore, p->info.brtDay); //Lấy thông tin trước khi thay đổi
			do
			{
				printf_s("\nNhap ngay thang nam sinh (So tuoi > 14, VD: 11/02/2005): ");
				gets_s(x.brtDay, 23);
				result = checkBrtDayFormat(x.brtDay);
				if (result == 0)
				{
					printf_s("\nDinh dang hoac thoi gian ban nhap vao khong dung! Moi nhap lai...\n");
				}
			} while (result != 1); //Nhập vào đúng định dạng thời gian, nếu sai phải nhập lại
			strcpy_s(p->info.brtDay, x.brtDay); //Cập nhật thông tin
			strcpy_s(getInfoAfter, p->info.brtDay); //Lấy thông tin sau khi thay đổi
			strcpy_s(feildUpdate, "Ngay thang nam sinh"); //Trường thông tin bị thay đổi
			writeLog(feildUpdate, getInfoBefore, getInfoAfter, p);//Ghi lại những thông tin trên vào file log
			break;
		case 3:
			strcpy_s(getInfoBefore, p->info.SDT); //Lấy thông tin trước khi thay đổi
			do
			{
				printf_s("\nNhap so dien thoai tinh nguyen vien: ");
				gets_s(x.SDT, 23);
				result = checkSDTFormat(x.SDT);
				if (result == 0)
				{
					printf_s("\nDinh dang ban nhap vao khong dung! Moi nhap lai...\n");
				}
			} while (result != 1); //Nhập vào đúng định dạng số điện thoại, nếu sai phải nhập lại
			result = checkSDT(lvt, x);  //Kiểm tra số điện thoại tình nguyện viên có trùng với số điện thoại đã có trong danh sách không
			if (result == 1)
			{
				printf_s("\nSo dien thoai trung voi tinh nguyen vien khac! Cap nhat khong thanh cong!\n");
				break; //nếu trùng thì dừng việc cập nhật và thoát ra menu chính 
			}
			else
			{
				strcpy_s(p->info.SDT, x.SDT); //Số điện thoại hợp lệ sẽ được cập nhật
				strcpy_s(getInfoAfter, p->info.SDT); //Lấy thông tin sau khi thay đổi
				strcpy_s(feildUpdate, "So dien thoai"); //Trường thông tin bị thay đổi
				writeLog(feildUpdate, getInfoBefore, getInfoAfter, p); //Ghi lại những thông tin trên vào file log
			}
			break;
		case 4:
			strcpy_s(getInfoBefore, p->info.MaCD); //Lấy thông tin trước khi thay đổi
			printf_s("\nNhap ma chien chien tinh nguyen vien tham gia: ");
			gets_s(x.MaCD, 11);
			if (strcmp(p->info.MaCD, x.MaCD) != 0)
			{
				result = checkMaCP(lcp, x);
				if (result == 1) //Nếu mã chiến dịch khớp với mã chiến dịch đã có trong danh sách thì sẽ tiếp tục cập nhật
				{
					strcpy_s(p->info.MaCD, x.MaCD); //Cập nhật thông tin
					strcpy_s(getInfoAfter, p->info.MaCD); //Lấy thông tin sau khi thay đổi
					strcpy_s(feildUpdate, "Ma chien dich"); //Trường thông tin bị thay đổi
					writeLog(feildUpdate, getInfoBefore, getInfoAfter, p);  //Ghi lại những thông tin trên vào file log
				}
				else //Nếu không tồn tại mã chiến dịch sẽ dường việc cập nhật và quay trở lại menu
				{
					printf_s("\nMa chien dich tham gia khong hop le!\n");
				}
			}
			else
			{
				//Nếu trùng với mã chiến dịch cũ thông tin sẽ không được cập nhật
				printf_s("\nMa chien dich ban nhap vao trung voi ma chien dich cu! Du lieu se khong duoc thay doi...\n");
			}
			break;
		default:
			printf_s("\nLua chon cua ban khong hop le! Moi chon lai!");
			break;
		}
	} while (luachon != 1 && luachon != 2 && luachon != 3 && luachon != 4);
}
void updateVLTandWriteLog(CampaignSList lcp, VolunteerSList lvt)
{
	if (isEmpty_lvt(lvt) == 1)
	{
		printf_s("\nDanh sach tinh nguyen vien rong! Khong the tim kiem...");
		return; //Hàm chỉ thực hiện khi tồn tại danh sách tình nguyện viên
	}

	int luachon, result;
	char input[15];
	VolunteerSNode* p;
	do
	{
		printf_s("\nChon truong thong tim muon tim kiem: ");
		printf_s("\n 1. Tim kiem theo ma tinh nguyen vien.");
		printf_s("\n 2. Tim kiem theo so dien thoai cua tinh nguyen vien.");
		printf_s("\nNhap lua chon cua ban: ");
		scanf_s("%d", &luachon);
		getchar();
		switch (luachon)
		{
		case 1:
			printf_s("\nNhap ma tinh nguyen vien:");
			gets_s(input);
			p = findVolunteerByMaTNV(lvt, input); //Tìm kiếm tình nguyện viên theo mã tình nguyện viên
			if (p == NULL) //Không tồn tại mã tình nguyện viên như đã nhập
			{
				printf_s("\nKhong tim thay tinh nguyen vien co ma %s!", input);
			}
			else
			{
				printf_s("\nDa tim ra tinh nguyen vien co ma %s!\n", input);
				showVolunteerSNode(p); //Hiển thị tình nguyện viên vừa tìm thấy

				updateInfomation(p, lcp, lvt); //Thực hiện cập nhật thông tin
				showVolunteerSNode(p); //Hiển thị thông tin tình nguyện viên vừa cập nhật
			}
			break;
		case 2:
			printf_s("\nNhap so dien thoai tinh nguyen vien:");
			gets_s(input);
			p = findVolunteerBySDT(lvt, input); //Tìm kiếm tình nguyện viên theo Số điện thoại tình nguyện viên
			if (p == NULL)
			{
				printf_s("\nKhong tim thay tinh nguyen vien co so dien thoai %s!", input); //Thông báo nếu không tìm thấy
			}
			else
			{
				printf_s("\nDa tim ra tinh nguyen vien co so dien thoai %s!\n", input);
				showVolunteerSNode(p); //Hiển thị tình nguyện viên vừa tìm thấy
				updateInfomation(p, lcp, lvt); //Thực hiện cập nhật thông tin
				showVolunteerSNode(p); //Hiển thị thông tin tình nguyện viên vừa cập nhật
			}
			break;
		default:
			printf_s("\nLua chon cua ban nhap vao khong hop le!");
			break;
		}
	} while (luachon != 1 && luachon != 2);

}