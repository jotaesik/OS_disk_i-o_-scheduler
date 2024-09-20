#include <stdio.h>	//����� ���
#include <stdlib.h>	//���� ����
#include <time.h>	//���� ����ð��ݿ�
#include <math.h>	//������ �Լ� ���
#include <conio.h>	//getch�Լ� ���
//��� �����: FCFS SSTF SCAN C-SCAN C-LOOK LOOK F-SCAN N-STEP SCAN �������� ����ť�� SLTF SPTF SATF FD-SCAN P-SCAN GSS-SCHEDUAL EDF-SCHEDUL SCAN-EDF-SCHE 
//�ʿ��� ���� ����
int which = 0;	//���°����� �����Ұ���
int headerposition = 0; //��������� ��ġ
int track[10] = { 0, };//������ Ʈ���� ��ġ
int count = 0;	//������ Ʈ���� ����
int seek_distance[10] = { 0, }; //�̵��Ÿ� ������
double ave_seek_time = 0;//���Ž���ð�
double ave_rotational_latency = 0;//��� ȸ�������ð�
int total_seek_distance = 0;	//��ü�̵��Ÿ�
double deviation[10] = { 0, };//���� �迭
double deviation2[10] = { 0, }; //���� ������ �迭
double variance = 0;//�л�
double total_deviation2 = 0;//���������� ��
double standard_deviation = 0;//ǥ������
int just = 0;	//�׳� ��� ���� ����
int sstf_distance[10] = { 0, };//sstf��� �ٷ궧 ���� ������ �̵��Ÿ� �Ź� �̵��Ÿ� �ּҰ� ���Ҷ� ���
int real_sstf_distance[10] = { 0, };//��¥ sstf ��� �̵��Ÿ�
int small = 0; //sstf��� ���� �Ÿ� �ּҰ�
int sstf_track[10] = { 0, };//sstf������� �Ÿ��� ���� track ������
int track_left = 0; //sstf ������� ���� track ����
int remain = 0;//sstf ������� ��ñ�����
int number = 0;//sstf������� while���ȿ��� number
int direction = 0;	//look���� ��������Լ�
int look_track[10] = { 0, };//look���� track
int look_distance[10] = { 0, };//look���� �Ÿ�
int look_order[10] = { 0, };//look���� order
int seek_time = 0;//seek_time �Է�
double total_rotational_latency = 0;	//��ȸ�������ð�
double rotational_latency[10] = { 0, };//ȸ�������ð�
double rpm = 0;	//�д�ȸ����
int sltf_track[10] = { 0, };//sltf ��������
int main(void) {
	printf("� ��ũ �����층 ����� �����Ͻðڽ��ϱ�?\n(1.FCFS��� 2.SSTF��� 3.LOOK��� 4.����ť�� ��� 5.�ñ��Ǳ��):");
	scanf("%d", &which);
	if (which == 1) {//FCFS
		printf("FCFS����� �����ϼ̽��ϴ�.");
		printf("\n���ũ ����� �ʱ���ġ�� �Է��ϼ���:(0���� 199����):");
		scanf("%d", &headerposition);
		printf("seek_time ���ذ��� �Է����ּ���:");
		scanf("%d", &seek_time);
		srand(time(NULL));//�����Լ�
		printf("�������� Ʈ���� ������ ���ص帮�ڽ��ϴ�(�ּ� 1����~�ִ� 10����)");
		count = rand() % 9 + 1;
		printf("\nƮ���� ������ %d�� ���������ϴ�.", count);
		printf("�Ǹ����� ������ 0~199�� �����߽��ϴ�.");
		printf("���� %d���� ���������������ϴ�.", count);
		for (int i = 0; i < count; i++) {
			track[i] = rand() % 200;
		}
		printf("\n������ Ʈ����ȣ�� ����: ");
		for (int i = 0; i < count; i++) {
			printf("%d, ", track[i]);
		}
		printf("\nFCFS����� ���������Ƿ� ������ ���� ��������̹Ƿ�:");
		for (int i = 0; i < count; i++) {
			printf("\n%d��°�� %d �Դϴ�.",i+1, track[i]);//��ȣ�� 0��°���� 1��°�� ���°� ���ؼ�
		}
		for (int i = 0; i < count; i++) {
			if (i == 0) {//ó���϶��� �������ġ�� �Ÿ��� ��Ƿ�
				just = track[i] - headerposition;	
				seek_distance[i] = abs(just);
			}
			else {
				just = track[i] - track[i - 1];
				seek_distance[i] = abs(just);
			}
		}
		printf("\n");
		for (int i = 0; i < count; i++) {
			if (i == 0) {
				printf("%d�� %d�� �̵��Ÿ��� %d�Դϴ�\n", headerposition,track[i],seek_distance[i]);
			}
			else {
				printf("%d�� %d�� �̵��Ÿ��� %d�Դϴ�.\n", track[i], track[i-1], seek_distance[i]);
			}
		}
		for (int i = 0; i < count; i++) {
			total_seek_distance = total_seek_distance + seek_distance[i];
		}
		printf("��ü �̵��Ÿ��� %d�Դϴ�.",total_seek_distance);
		printf("\nseek_time�� %d�̹Ƿ� �� Ž���ð��� %d�Դϴ�.�� ȸ�������ð��� �����Ƿ� �� ����ð��� %d�Դϴ�.",seek_time,total_seek_distance * seek_time, total_seek_distance * seek_time);
		ave_seek_time = (total_seek_distance * seek_time)/count;
		printf("�׸��� ��� Ž���ð��� %lf�Դϴ�.\n", ave_seek_time);
		for (int i = 0; i < count; i++) {
			deviation[i] = (seek_distance[i] * seek_time) - ave_seek_time;
			printf("�� %d ��°  Ž���ð� %d�� ���� ������ %lf�Դϴ�.", i+1,seek_distance[i] * seek_time, deviation[i]);
			deviation2[i] = (deviation[i]*deviation[i]);
			printf("�� ������ ������ %lf�Դϴ�.\n", deviation2[i]);
			total_deviation2 = total_deviation2 + deviation2[i];
		}
		variance = total_deviation2 / count;
		printf("�� ������ ���� %lf�̹Ƿ� �л��� %lf �Դϴ�.", total_deviation2, variance);
		standard_deviation = sqrt(variance);
		printf("�׷��Ƿ� ����ð��� ǥ�������� %lf�Դϴ�.", standard_deviation);
	}
	else if (which == 2) {//SSTF
		printf("SSTF����� �����ϼ̽��ϴ�.");
		printf("\n���ũ ����� �ʱ���ġ�� �Է��ϼ���:(0���� 199����):");
		scanf("%d", &headerposition);
		printf("seek_time ���ذ��� �Է����ּ���:");
		scanf("%d", &seek_time);
		srand(time(NULL));
		printf("�������� Ʈ���� ������ ���ص帮�ڽ��ϴ�(�ּ� 1����~�ִ� 10����)");
		count = rand() % 9 + 1;
		printf("\nƮ���� ������ %d�� ���������ϴ�.", count);
		printf("�Ǹ����� ������ 0~199�� �����߽��ϴ�.");
		printf("%d���� ���������������ϴ�.", count);
		for (int i = 0; i < count; i++) {
			track[i] = rand() % 200;
			sstf_track[i] = track[i];
		}
		printf("\n������ Ʈ����ȣ: ");
		for (int i = 0; i < count; i++) {
			printf("%d ", track[i]);
		}
		printf("\nSSTF����� ���������Ƿ� ������:\n");
		track_left = count;	//�� Ʈ���� ���� ����
		int just1 = 0;
		while (track_left >0) {	//Ʈ���� ������ 0�� �ɶ�����
			if (track_left == count) {	//ù������ ���Ҷ� �����ġ�� ���ؾ��ϹǷ�
				for (int i = 0; i < count; i++) {
					sstf_distance[i] = abs(headerposition - sstf_track[i]);	//������ �̵��Ÿ� ����
				}
				small = 200;	//�ּڰ��� ã������ ���Ƿ� 200 ����
				for (int i = 0; i < count; i++) {
					if (sstf_distance[i] < small) {	
						small = sstf_distance[i];
						seek_distance[number] = small;	//�ּڰ��� ã������ �ٽ� ����
						just = i;	//�ּڰ��϶��� i�� just�� ���� ���������ʹ� ��ģ���� �����ϰ� �Ÿ�����ϹǷ�
						real_sstf_distance[just1] = sstf_distance[i];	//�ּڰ��϶��� �� Ž���Ÿ��� real�迭�� ����
						remain = sstf_track[just];	//remain�̶�� ���� �ּڰ��϶� Ʈ����ȣ�� ����
					}
				}
				printf("%d��°�� %d�� �� �����Ƿ�\n", number+1, remain);
				sstf_track[just] = 1000;	//�������ʹ� �����ϰ� �Ÿ���Ƿ� 1000�̶�� ū���� �Է�
			}
			else {	//ù������ �����ϰ�� ���� ������� ��ġ�� ���ؾ��ϹǷ�
				for (int i = 0; i < count; i++) {
					sstf_distance[i] = abs(remain - sstf_track[i]);	//remain�� ����Ȱ��� ���� �޴� Ʈ����ȣ�̹Ƿ�
				}
				small = 200;
				for (int i = 0; i < count; i++) {
					if (sstf_distance[i] < small) {
						small = sstf_distance[i];
						seek_distance[number] = small;
						just = i;
						real_sstf_distance[just1] = sstf_distance[i];
						remain = sstf_track[just];
						
					}
				}
				printf("%d��°�� %d�� �� �����Ƿ�\n", number+1, remain);
				sstf_track[just] = 1000;
			}
			number++;	//���° üũ
			track_left--;	//���� Ʈ��üũ
			just1++;	//�̵��Ÿ�
		}
		for (int i = 0; i < count; i++) {
			total_seek_distance = total_seek_distance + seek_distance[i];
		}
		printf("��ü �̵��Ÿ���:%d", total_seek_distance);	
		printf("\nseek_time�� %d�̹Ƿ� �� Ž���ð��� %d�Դϴ�",seek_time,total_seek_distance* seek_time);
		printf("�� ȸ�������ð��� �����Ƿ� �� ����ð��� %d�Դϴ�.",total_seek_distance* seek_time);
		ave_seek_time = (total_seek_distance * seek_time) / count;
		printf("��� Ž���ð��� %lf�Դϴ�.\n", ave_seek_time);
		for (int i = 0; i < count; i++) {
			deviation[i] = (seek_distance[i] * seek_time) - ave_seek_time;
			printf("�� %d��° Ž���ð� %d�� ���� ������ %lf�Դϴ�.", i + 1, seek_distance[i] * seek_time, deviation[i]);
			deviation2[i] = (deviation[i] * deviation[i]);
			printf("�� ������ ������ %lf�Դϴ�.\n", deviation2[i]);
			total_deviation2 = total_deviation2 + deviation2[i];
		}
		variance = total_deviation2 / count;
		printf("�� ������ ���� %lf�̹Ƿ� �л��� %lf�Դϴ�.", total_deviation2, variance);
		standard_deviation = sqrt(variance);
		printf("�׷��Ƿ� ǥ�������� %lf�Դϴ�.", standard_deviation);
	}
	else if (which == 3) {//LOOK
		printf("LOOK����� �����ϼ̽��ϴ�.");
		printf("\n���ũ ����� �ʱ���ġ�� �Է��ϼ���:(0���� 199����):");
		scanf("%d", &headerposition);
		printf("seek_time ���ذ��� �Է����ּ���:");
		scanf("%d", &seek_time);
		srand(time(NULL));
		printf("�������� Ʈ���� ������ ���ص帮�ڽ��ϴ�(�ּ� 1����~�ִ� 10����)");
		count = rand() % 9 + 1;
		printf("Ʈ���� ������ %d�� ���������ϴ�.", count);
		printf("�Ǹ����� ������ 0~199�� �����߽��ϴ�.");
		printf("\n%d���� ���������������ϴ�.", count);
		for (int i = 0; i < count; i++) {
			track[i] = rand() % 200;
			look_track[i] = track[i];
		}
		printf("\n������ Ʈ����ȣ�� ����: ");
		for (int i = 0; i < count; i++) {
			printf("%d ", track[i]);
		}
		printf("\n������������ ��迭�� ����:");	//headerposition ���� ū�Ŷ� ������ ������ ��迭�ϱ�.
		for (int i = 0; i < count; i++) {
			for (int j = 0; j < count - 1; j++) {
				if (look_track[j] > look_track[j+1]) {
					just = look_track[j];
					look_track[j] = look_track[j + 1];
					look_track[j+1] = just;
				}
			}
		}
		for (int i = 0; i < count; i++) {
			printf("%d ", look_track[i]);
		}
		printf("\n��� �������� ��带 �������� ������ ���ϼ���.(1.�ö󰡴¹��� 2.�������¹���):");
		scanf("%d", &direction);
		remain = 0;
		number = 0;
		if (direction == 1) {	//�ö󰡴¹����϶�
			printf("LOOK����� ���ð� ������ �ö󰡴¹����̹Ƿ�  ������:");
			for (int i = 0; i < count; i++) {	//��������Ǻ��� ū������ �������
				if (headerposition <= look_track[i]) {
					look_order[remain] = look_track[i];
					remain++;
				}
			}
			number = remain;
			for (int i = 0; i < count; i++) {	//��������Ǻ��� ���������� �������
				if (headerposition > look_track[i]) {
					look_order[remain] = look_track[i];
					remain++;
				}
			}
			for (int i = number; i < count; i++) {	//�������� ����
				for (int j = number; j < count - 1; j++) {
					if (look_order[j] < look_order[j + 1]) {
						just = look_order[j];
						look_order[j] = look_order[j + 1];
						look_order[j + 1] = just;
					}
				}
			}
			for (int i = 0; i < count; i++) {
				printf("%d ", look_order[i]);
			}
			for (int i = 0; i < count; i++) {
				if (i == 0) {
					look_distance[i] = abs(headerposition - look_order[i]);
				}
				else {
					look_distance[i] = abs(look_order[i] - look_order[i - 1]);
				}
			}
			printf("\n�� �̵��Ÿ���: ");
			for (int i = 0; i < count; i++) {
				total_seek_distance = total_seek_distance + look_distance[i];
			}
			printf("%d", total_seek_distance);
			printf("\nseek_time�� %d�̹Ƿ� �� Ž���ð��� %d�Դϴ�.", seek_time,total_seek_distance* seek_time);
		}
		else if (direction == 2) {	//�������¹���
			printf("LOOK����� �����߰� ������ �������¹����̹Ƿ� ������:");
			for (int i = 0; i < count; i++) {
				if (headerposition >= look_track[i]) {
					look_order[remain] = look_track[i];
					remain++;
				}
			}
			number = remain;
			for (int i = 0; i < count; i++) {
				if (headerposition < look_track[i]) {
					look_order[remain] = look_track[i];
					remain++;
				}
			}
			for (int i = 0; i < number; i++) {
				for (int j = 0; j < number - 1; j++) {
					if (look_order[j] < look_order[j + 1]) {
						just = look_order[j];
						look_order[j] = look_order[j + 1];
						look_order[j + 1] = just;
					}
				}
			}
			for (int i = 0; i < count; i++) {
				printf("%d ", look_order[i]);
			}
			for (int i = 0; i < count; i++) {
				if (i == 0) {
					look_distance[i] = abs(headerposition - look_order[i]);
				}
				else {
					look_distance[i] = abs(look_order[i] - look_order[i - 1]);
				}
			}
			printf("\n�� �̵��Ÿ���: ");
			for (int i = 0; i < count; i++) {
				total_seek_distance = total_seek_distance + look_distance[i];
			}
			printf("%d", total_seek_distance);
			printf("\nseek_time�� %d�̹Ƿ� �� Ž���ð��� %d�Դϴ�", seek_time,total_seek_distance* seek_time);
		}
		else {
			printf("�ùٸ��� ���� �����Դϴ�.");
		}
		printf("�� ȸ�������ð��� �����Ƿ� �� ����ð��� %d�Դϴ�.", total_seek_distance * seek_time);
		ave_seek_time = (total_seek_distance * seek_time) / count;
		printf("��� Ž���ð��� %lf�Դϴ�.\n", ave_seek_time);
		for (int i = 0; i < count; i++) {
			deviation[i] = (look_distance[i] * seek_time) - ave_seek_time;
			printf("�� %d ��°  Ž���ð� %d�� ���� ������ %lf�Դϴ�.", i + 1, look_distance[i] * seek_time, deviation[i]);
			deviation2[i] = (deviation[i] * deviation[i]);
			printf("�� ������ ������ %lf�Դϴ�.\n", deviation2[i]);
			total_deviation2 = total_deviation2 + deviation2[i];
		}
		variance = total_deviation2 / count;
		printf("�� ������ ���� %lf�̹Ƿ� �л��� %lf �Դϴ�.", total_deviation2, variance);
		standard_deviation = sqrt(variance);
		printf("\n�׷��Ƿ� ǥ�������� %lf�Դϴ�.", standard_deviation);
	}
	else if (which == 4) {//����ť��
		printf("����ť�� ����� �����ϼ̽��ϴ�.");
		printf("\n���ũ ����� �ʱ���ġ�� �Է��ϼ���:(0���� 199����):");
		scanf("%d", &headerposition);
		printf("��ũ�� rpm ���ذ��� �Է����ּ���(5400,6000,7200 ���):");
		scanf("%lf", &rpm);
		srand(time(NULL));
		printf("�������� Ʈ���� ������ ���ص帮�ڽ��ϴ�(�ּ� 1����~�ִ� 10����).");
		count = rand() % 9 + 1;
		printf("Ʈ���� ������ %d�� ���������ϴ�.", count);
		printf("�Ǹ����� ������ 0~199�� �����߽��ϴ�.");
		printf("%d���� ���������������ϴ�.", count);
		for (int i = 0; i < count; i++) {
			track[i] = rand() % 200;
		}
		printf("\n������ Ʈ����ȣ�� ����:");
		for (int i = 0; i < count; i++) {
				printf("%d ", track[i]);
		}
		printf("\n");
		double sec_rpm = rpm / 60;	//�ʴ� ȸ����
		double ms_rpm = sec_rpm / 1000;	//ms�� ȸ����
		double clock = 1 / ms_rpm;	//1ȸ���ϴµ� �ɸ��½ð� ���� ms
		printf("��ũ�� �ѹ��� ȸ���ϴµ� �ɸ��ð� %lf�Դϴ�.", clock);
		int sector_number = 0;	//���Ͱ���
		printf("\n����ť���� �����ϼ̽��ϴ�.Ʈ���� �ϳ��̹Ƿ� seek time�� �����ϴ�. ������ ������ �Է��ϼ���(4,8,10�� �Է�):");
		scanf("%d", &sector_number);
		if ((sector_number == 4) || (sector_number == 8) || (sector_number == 10)) {
			printf("�ùٸ� ������ �����Դϴ�.������ ���� %d�� �Է��ϼ����Ƿ� 0~199������ �з��ϰڽ��ϴ�. ", sector_number);
		}
		else {
			printf("���� �����Դϴ�.");
		}
		if (sector_number == 4) {
			int width = 200 / 4;	//�Ѽ��ʹ�
			int counter = 0;
			int left = 0;	//���μ���
			int up = 0;	//���Ʒ�
			int headersector = 0;	//ó�� �Է��� ��������� ��ġ
			double real_clock = clock / 4;//�����ϳ����µ� �ɸ��½ð�;
			printf("\n���Ͱ� 4���Դϴ�.");
			for (int j = 0; j < 4; j++) {	//��弽�ͱ��ϱ�
				if (j * width <= headerposition && headerposition <= (j + 1) * width - 1) {
					headersector = j;
				}
			}
			printf("�ʱ⿡ ����������� %d�� �����ϼ˽��ϴ�.������ sector�� ������ 4���� ���ϼ�����, ���� ����� ��ġ�� ����%d�Դϴ�\n", headerposition, headersector);
			int sector[4][10] = { 0, };
			int sector_number[4][10] = { 0, };
			int sector_order[10] = { 0, };
			for (int j = 0; j < 4; j++) {//���Ϳ��°� �����ϱ�
				for (int i = 0; i < count; i++) {
					if (j * width <= track[i] && track[i] <= (j + 1) * width - 1) {
						sector[left][up] = track[i];
						sector_number[left][up] = j + 1;
						up++;
					}
				}
				left++;
				up = 0;
			}
			printf("0�� ���� Ʈ���� ���ٴ°��Դϴ�.\n");
			for (int i = 0; i < 4; i++) {
				printf("%d�������� %d������ ���� %d \t ", i * width, (i + 1) * width - 1, i);
				for (int j = 0; j < 10; j++) {
					printf("%d ", sector[i][j]);
				}
				printf("\n");
			}
			printf("ť�� ���Ϳ� ���� �з������� ����ť�׿� ���� ������: ");
			counter = 0;
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 4; j++) {
					if (sector[j][i] != 0) {
						sltf_track[counter] = sector[j][i];
						sector_order[counter] = sector_number[j][i];
						counter++;
					}
				}
			}
			for (int i = 0; i < count; i++) {
				printf("%d ", sltf_track[i]);
			}
			printf("\n");
			printf("��ũ�� �ѹ��� ȸ���ϴµ� �ɸ��ð� %lf�Դϴ�.\n�� 1/4���� ���µ� �ɸ��� �ð��� %lf�̰� \n2/4���� ���µ� �ɸ��� �ð��� %lf�̰� \n3/4���� ���µ� �ɸ��� �ð��� %lf�Դϴ�. \n", clock,clock/4,clock/2,clock*3/4);
			printf("�׷��ٸ� ȸ�������ð���? ó�� �����ġ�� %d�����̹Ƿ� ", headersector);
			for (int i = 0; i < count; i++) {
				if (i == 0) {
					if (sector_order[i] >= headersector) {
						rotational_latency[i] = real_clock * abs(sector_order[i] - headersector);
					}
					else {
						rotational_latency[i] = real_clock * (4 - abs(sector_order[i] - headersector));
					}
				}
				else {
					if (sector_order[i] >= sector_order[i - 1]) {
						rotational_latency[i] = real_clock * abs(sector_order[i] - sector_order[i - 1]);
					}
					else {
						rotational_latency[i] = real_clock * (4 - abs(sector_order[i] - sector_order[i - 1]));
					}
				}
			}
			printf("\n");
			for (int i = 0; i < count; i++) {
				printf("%lf ", rotational_latency[i]);
			}
			printf("\n");
			for (int i = 0; i < count; i++) {
				total_rotational_latency = total_rotational_latency + rotational_latency[i];
			}
			printf("��ü ȸ���ð��� %lf�Դϴ�", total_rotational_latency);
		}
		else if (sector_number == 8) {
			int width = 200 / 8;
			int counter = 0;
			int left = 0;	//���μ���
			int up = 0;	//���Ʒ�
			int headersector = 0;
			double real_clock = clock / 8;//�����ϳ����µ� �ɸ��½ð�;
			printf("\n���Ͱ� 8���Դϴ�.");
			for (int j = 0; j < 8; j++) {
				if (j * width <= headerposition && headerposition <= (j + 1) * width - 1) {
					headersector = j;
				}
			}
			printf("�ʱ⿡ ����������� %d�� �����ϼ˽��ϴ�.������ sector�� ������ 8���� ���ϼ�����,���� ����� ��ġ�� ����%d�Դϴ�\n", headerposition, headersector);
			int sector[8][10] = { 0, };
			int sector_number[8][10] = { 0, };
			int sector_order[10] = { 0, };
			for (int j = 0; j < 8; j++) {
				for (int i = 0; i < count; i++) {
					if (j * width <= track[i] && track[i] <= (j + 1) * width - 1) {
						sector[left][up] = track[i];
						sector_number[left][up] = j + 1;
						up++;
					}
				}
				left++;
				up = 0;
			}
			printf("0�� Ʈ���� ���°̴ϴ�.\n");
			for (int i = 0; i < 8; i++) {
				printf("%d�������� %d������ ���� %d \t ", i * width, (i + 1) * width - 1, i);
				for (int j = 0; j < 10; j++) {
					printf("%d ", sector[i][j]);
				}
				printf("\n");
			}
			printf("ť�� ���Ϳ� ���� �з������� ����ť�׿� ���� ������:");
			counter = 0;
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 8; j++) {
					if (sector[j][i] != 0) {
						sltf_track[counter] = sector[j][i];
						sector_order[counter] = sector_number[j][i];
						counter++;
					}
				}
			}
			for (int i = 0; i < count; i++) {
				printf("%d ", sltf_track[i]);
			}
			printf("\n��ũ�� �ѹ��� ȸ���ϴµ� �ɸ��ð� %lf�Դϴ�.\n�� 1/8���� ���µ� �ɸ��� �ð��� %lf�̰� \n2/8���� ���µ� �ɸ��� �ð��� %lf�̰� \n3/8���� ���µ� �ɸ��� �ð��� %lf�̰�\n", clock, clock / 8, clock*2 / 8, clock * 3 / 8);
			printf("4/8���� ���µ� �ɸ��� �ð��� %lf�̰�\n5/8���� ���µ� �ɸ��� �ð��� %lf�̰� \n6/8���� ���µ� �ɸ��� �ð��� %lf�̰�\n7/8���� ���µ� �ɸ��� �ð��� %lf�Դϴ�\n", clock*4/8, clock*5 / 8, clock * 6 / 8, clock * 7 / 8);
			printf("�׷��ٸ� ȸ�������ð���? ó�� �����ġ�� %d�����̹Ƿ� ", headersector);
			for (int i = 0; i < count; i++) {
				if (i == 0) {
					if (sector_order[i] >= headersector) {
						rotational_latency[i] = real_clock * abs(sector_order[i] - headersector);
					}
					else {
						rotational_latency[i] = real_clock * (8 - abs(sector_order[i] - headersector));
					}
				}
				else {
					if (sector_order[i] >= sector_order[i - 1]) {
						rotational_latency[i] = real_clock * abs(sector_order[i] - sector_order[i - 1]);
					}
					else {
						rotational_latency[i] = real_clock * (8 - abs(sector_order[i] - sector_order[i - 1]));
					}
				}
			}
			printf("\n");
			for (int i = 0; i < count; i++) {
				printf("%lf ", rotational_latency[i]);
			}
			printf("\n");
			for (int i = 0; i < count; i++) {
				total_rotational_latency = total_rotational_latency + rotational_latency[i];
			}
			printf("��ü ȸ���ð��� %lf�Դϴ�", total_rotational_latency);
		}
		else {
			int width = 200 / 10;
			int counter = 0;
			int left = 0;	//���μ���
			int up = 0;	//���Ʒ�
			int headersector = 0;
			double real_clock = clock / 10;//�����ϳ����µ� �ɸ��½ð�;
			printf("\n���Ͱ� 10���Դϴ�.");
			for (int j = 0; j < 10; j++) {
				if (j * width <= headerposition && headerposition <= (j + 1) * width - 1) {
					headersector = j;
				}
			}
			printf("�ʱ⿡ ����������� %d�� �����ϼ˽��ϴ�.������ sector�� ������ 10���� ���ϼ�����, ���� ����� ��ġ�� ����%d�Դϴ�\n", headerposition, headersector);
			int sector[10][10] = { 0, };
			int sector_number[10][10] = { 0, };
			int sector_order[10] = { 0, };
			for (int j = 0; j < 10; j++) {
				for (int i = 0; i < count; i++) {
					if (j * width <= track[i] && track[i] <= (j + 1) * width - 1) {
						sector[left][up] = track[i];
						sector_number[left][up] = j + 1;
							up++;
					}
				}
				left++;
				up = 0;
			}
			printf("0�ΰ��� Ʈ����ȣ�� ���� ���Դϴ�.\n");
			for (int i = 0; i < 10; i++) {
				printf("%d�������� %d������ ���� %d \t ", i * width, (i + 1) * width - 1, i);
				for (int j = 0; j < 10; j++) {
					printf("%d ", sector[i][j]);
				}
				printf("\n");
			}
			printf("ť�� ���Ϳ� ���� �з������� ����ť�׿� ���� ������:");
			counter = 0;
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (sector[j][i] != 0) {
						sltf_track[counter] = sector[j][i];
						sector_order[counter] = sector_number[j][i];
						counter++;
					}
				}
			}
			for (int i = 0; i < count; i++) {
				printf("%d ", sltf_track[i]);
			}
			printf("\n��ũ�� �ѹ��� ȸ���ϴµ� �ɸ��ð� %lf�Դϴ�.\n�� 1/10���� ���µ� �ɸ��� �ð��� %lf�̰� \n2/10���� ���µ� �ɸ��� �ð��� %lf�̰� \n3/10���� ���µ� �ɸ��� �ð��� %lf�̰�\n", clock, clock / 10, clock * 2 / 10, clock * 3 / 10);
			printf("4/10���� ���µ� �ɸ��� �ð��� %lf�̰� \n5/10���� ���µ� �ɸ��� �ð��� %lf�̰� \n6/10���� ���µ� �ɸ��� �ð��� %lf�̰�\n7/10���� ���µ� �ɸ��� �ð��� %lf�̰�\n", clock * 4 / 10, clock * 5 / 10, clock * 6 / 10, clock * 7 / 10);
			printf("8/10���� ���µ� �ɸ��� �ð��� %lf�̰� \n9/10���� ���µ� �ɸ��� �ð��� %lf�Դϴ�.\n", clock * 8 / 10, clock * 9 / 10);
			printf("�׷��ٸ� ȸ�������ð���? ó�� �����ġ�� %d�����̹Ƿ� ", headersector);
			for (int i = 0; i < count; i++) {
				if (i == 0) {
					if (sector_order[i] >= headersector) {
						rotational_latency[i] = real_clock * abs(sector_order[i] - headersector);
					}
					else {
						rotational_latency[i] = real_clock * (10 - abs(sector_order[i] - headersector));
					}
				}
				else {
					if (sector_order[i] >= sector_order[i - 1]) {
						rotational_latency[i] = real_clock * abs(sector_order[i] - sector_order[i - 1]);
					}
					else {
						rotational_latency[i] = real_clock * (10 - abs(sector_order[i] - sector_order[i - 1]));
					}
				}

			}
			printf("\n");
			for (int i = 0; i < count; i++) {
				printf("%lf ", rotational_latency[i]);
			}
			printf("\n");
			for (int i = 0; i < count; i++) {
				total_rotational_latency = total_rotational_latency + rotational_latency[i];
			}
			printf("��ü ȸ���ð��� %lf�Դϴ�", total_rotational_latency);
		}
		printf("�� ȸ�������ð��� %lf�Դϴ�.�� Ž���ð��� �����Ƿ� �� ����ð��� %lf�Դϴ�.", total_rotational_latency, total_rotational_latency);
		ave_rotational_latency = total_rotational_latency / count;
		printf("��� ȸ�������ð��� %lf�Դϴ�.\n", ave_rotational_latency);
		for (int i = 0; i < count; i++) {
			deviation[i] = rotational_latency[i] - ave_rotational_latency;
			printf("�� %d ��°  ȸ�������ð�%lf �� ���� ������ %lf�Դϴ�.", i + 1, rotational_latency[i], deviation[i]);
			deviation2[i] = (deviation[i] * deviation[i]);
			printf("�� ������ ������ %lf�Դϴ�.\n", deviation2[i]);
			total_deviation2 = total_deviation2 + deviation2[i];
		}
		variance = total_deviation2 / count;
		printf("�� ������ ���� %lf�̹Ƿ� �л��� %lf �Դϴ�.", total_deviation2, variance);
		standard_deviation = sqrt(variance);
		printf("�׷��Ƿ� ǥ�������� %lf�Դϴ�.", standard_deviation);
		printf("\n\n");
	}
	else if (which == 5) {//�ñ��Ǳ��
		printf("�ñ��Ǳ���� �����ϼ̽��ϴ�.�������� ������ ����� P-SCAN�� SATF����� ������ �켱������ ������ ���۽ð��� ���ÿ� ����� ����� ���� ���°Ͱ��Ѵ�.\n�ñ��Ǳ��: �ƹ��� �켱������ ���Ƶ� ���������۽ð��� ");
		printf("�������� �ڿ� �ִ� �͵��� �ʰ԰ɸ��Ƿ� �켱������ ������ũ�⸦ ��ȭ�Ӱ� ó���Ҽ��մ� ����� �����غ��Ҵ�. ");
		printf("\n�ñ��Ǳ���� �����ϼ̽��ϴ�.");
		printf("\n���ũ ����� �ʱ���ġ�� �Է��ϼ���:(0���� 199����):");
		scanf("%d", &headerposition);
		printf("seek_time ���ذ��� �Է����ּ���:");
		scanf("%d", &seek_time);
		printf("��ũ�� rpm ���ذ�(��ũ�� �д� ȸ����)�� �Է����ּ���(����ϵ��ũ�� 3600rpm���� 5400rpm 7200rpm):");
		scanf("%lf", &rpm);
		srand(time(NULL));
		printf("�������� Ʈ���� ������ ���ص帮�ڽ��ϴ�(�ּ� 1����~�ִ� 10����).");
		count = rand() % 9 + 1;
		printf("Ʈ���� ������ %d�� ���������ϴ�.", count);
		printf("�Ǹ����� ������ 0~199�� �����߽��ϴ�.");
		printf("\n%d���� ���������������ϴ�.", count);
		int a[10][4] = { 0, };	//Ʈ��, �켱���� ������
		for (int i = 0; i < count; i++) {
			a[i][0] = rand() % 200;
		}
		printf("\n������ Ʈ����ȣ�� ����: ");
		for (int i = 0; i < count; i++) {
			printf("%d ", a[i][0]);
		}
		double sec_rpm = rpm / 60;	//�ʴ� ȸ����
		double ms_rpm = sec_rpm / 1000; //ms�ʴ� ȸ����
		double one_time = 1 / ms_rpm; //1������ �ɸ��� ms
		printf("\n��ũ�� 1�ʴ� ȸ���ϴ� Ƚ���� %lf�����Դϴ�.", sec_rpm);
		printf("��ũ�� 1ms�ʴ� ȸ���ϴ� Ƚ���� %lf�����Դϴ�.", ms_rpm);
		printf("��ũ�� 1������ ���µ��ɸ��� �ð��� %lf ms�Դϴ�.", one_time);
		double track_byte = 0;
		printf("\nƮ��ũ�⸦ �����ּ���(10^3 �̻� 10^8����):");
		scanf("%lf", &track_byte);
		printf("��Ʈ���� ũ��� %lf byte�Դϴ�.", track_byte);
		double dump = one_time / 1000;
		printf("\n��ũ�� %lf�ʴ� �����ϴ� ���� %lf byte�Դϴ�.", one_time / 1000, track_byte);
		printf("\n��ũ�� 1�ʴ� �����ϴ� ���� %lf byte�Դϴ�.", track_byte * (1 / dump));
		double mega = track_byte * (1 / dump) / 1000000;
		printf("\n��ũ�� 1�ʴ� �����ϴ� ���� %lf Mbyte�Դϴ�.", mega);
		printf("\n���� ������ �켱������ ������ũ�⸦ �Է��մϴ�.\n");
		printf("Ʈ����ȣ �켱���� ������ũ��(���� Mbyte)(�Է��ϰ� tab�� �����ּ���)\n");
		for (int i = 0; i < count; i++) {
			printf("%d�� �켱���� �Է�, ������ũ�� �Է�: ", a[i][0]);
			scanf("%d %d", &a[i][1], &a[i][2]);
		}
		for (int i = 0; i < count; i++) {
			a[i][3] = a[i][1] * a[i][2];
		}
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		for (int i = 0; i < count; i++) {
			printf("%d�� �켱���� %d ������ũ�� %d Mbyte ��� %d \n", a[i][0], a[i][1], a[i][2], a[i][3]);
		}
		int user = 0;
		int trash3 = 0;
		int trash2 = 0;
		int trash1 = 0;
		int trash0 = 0;
		for (int i = 0; i < count; i++) {	//��п� ���� ���� ����
			for (int j = 0; j < count - 1; j++) {
				if (a[j][3] > a[j + 1][3]) {
					trash3 = a[j][3];
					a[j][3] = a[j + 1][3];
					a[j + 1][3] = trash3;
					trash2 = a[j][2];
					a[j][2] = a[j + 1][2];
					a[j + 1][2] = trash2;
					trash1 = a[j][1];
					a[j][1] = a[j + 1][1];
					a[j + 1][1] = trash1;
					trash0 = a[j][0];
					a[j][0] = a[j + 1][0];
					a[j + 1][0] = trash0;
				}
			}
		}
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n�켱������ �������� �翡 ���� ������ ���ϸ�:\n");
		for (int i = 0; i < count; i++) {
			printf("%d��°�δ� ����� %d�� %d�� ���۵ȴ�.\n",i+1, a[i][3], a[i][0]);
		}
		for (int i = 0; i < count; i++) {
			if (i == 0) {
				seek_distance[i] = abs(headerposition - a[i][0]);
			}
			else {
				seek_distance[i] = abs(a[i-1][0] - a[i][0]);
			}
		}
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		for (int i = 0; i < count; i++) {
			if (i == 0) {
				printf("%d ���� %d�� �̵��Ѵ�. �� �̵��Ÿ���%d �̴�\n",headerposition,a[i][0],seek_distance[i]);
			}
			else {
				printf("%d ���� %d�� �̵��Ѵ�.�� �̵��Ÿ��� %d�̴�\n", a[i-1][0], a[i][0],seek_distance[i]);
			}
		}
		for (int i = 0; i < count; i++) {
			total_seek_distance = total_seek_distance + seek_distance[i];
		}
		printf("\n��ü �̵��Ÿ��� %d�Դϴ�.\n", total_seek_distance);
		double taesik_seek_time[10] = { 0, };
		for (int i = 0; i < count; i++) {
			taesik_seek_time[i] = seek_distance[i] * seek_time;
		}
		double transport_time[10] = { 0, };//������ ���۽ð�
		for (int i = 0; i < count; i++) {
			transport_time[i] = a[i][2] / mega;
			printf("%d��°�� %d Mbyte ������ ���۽ð��� %lf�̴�.\n", i + 1, a[i][2], transport_time[i]);
		}
		double response_time[10] = { 0, };//����ð�
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		for (int i = 0; i < count; i++) {
			if (i == 0) {
				response_time[i] = taesik_seek_time[i] + transport_time[i];
			}
			else {
				response_time[i] = taesik_seek_time[i] + transport_time[i] + response_time[i - 1];
			}
		
			printf("%d��°�� %d ��ȣ�� ����ð� %lf�̴�.\n", i + 1, a[i][0], response_time[i]);
		}
		printf("\n�� ����ð��� %lf�Դϴ�.�� ȸ�������ð��� �����Ƿ� �� ����ð��� %lf�Դϴ�.", response_time[count-1],response_time[count-1]);
		double ave_response_time = 0;
		ave_response_time = response_time[count-1] / count;
		printf("\n��� ����ð��� %lf�Դϴ�.\n", ave_response_time);
		for (int i = 0; i < count; i++) {
			deviation[i] = response_time[i] - ave_response_time;
			printf("�� %d ��°  ����ð�%lf �� ���� ������ %lf�Դϴ�.", i + 1, response_time[i], deviation[i]);
			deviation2[i] = (deviation[i] * deviation[i]);
			printf("�� ������ ������ %lf�Դϴ�.\n", deviation2[i]);
			total_deviation2 = total_deviation2 + deviation2[i];
		}
		variance = total_deviation2 / count;
		printf("�� ������ ���� %lf�̹Ƿ� �л��� %lf �Դϴ�.", total_deviation2, variance);
		standard_deviation = sqrt(variance);
		printf("�׷��Ƿ� ǥ�������� %lf�Դϴ�.", standard_deviation);
	}
	else {
		printf("����� ������ ����� ���� ��ũ �����층 ����Դϴ�.");
	}
	getch();
	return 0;
}