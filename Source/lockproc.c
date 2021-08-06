#include "lockproc.h"
#include "ssec.h"
#include "mygpio.h"

// ������� �������
// 0 - ������ �� ������
// 10 - ������� �� �������� �����
// 11 - ���� ������� �������� �����
// 20 - ������� �� �������� �����
// 21 - ���� �������� �����
// 30 - ����� ����� ���������� ��������
int16_t doorst = 0;

// ������� ������� �������� ��� �������� �����
// 0 - ���������
// 1 - ���������
void DoorCmd(uint8_t cmd) {
	if (doorst) return; // ���-�� �����������, ������� ��������� ������
	if (cmd) {
		doorst=10;
	} else {
		doorst=20;
	}
}

void opendoor(void) {
	static uint32_t dtime=0; // ����� ��������
  switch (doorst) {
		case (0):       // ������ �� ������. �� ������ ������ ��������� ����
			GResetPin(RELAYOPEN);  	
			GResetPin(RELAYCLOSE);
			break;
		case (10):              // ������� ���������� �����
			GSetPin(RELAYOPEN);
		  dtime=getssec();
		  doorst=11;
		  break;
		case (11):              // ����������� ������� ���������� �����
			if (tdlt(dtime)>300) {
				doorst=30;
				GResetPin(RELAYOPEN);
				dtime=getssec();
			}
			break;
		case (20):              // ������� ���������� �����
			GSetPin(RELAYCLOSE);
		  dtime=getssec();
		  doorst=21;
		  break;
		case (21):              // ����������� ������� ���������� �����
			if (tdlt(dtime)>300) {
				doorst=30;
				GResetPin(RELAYCLOSE);
				dtime=getssec();
			}
			break;	
	  case (30):
			if (tdlt(dtime)>500) {
				dtime=0;
				doorst=0;
			}
			break;
		default:
			doorst=0; // �� ������ ������
	}
}
 
