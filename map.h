#ifndef MAP_H //��d��include����邱�Ƃ�h��
#define MAP_H

#define MAX_X 20	//X���W�̍ő�l
#define MAX_Y 20	//Y���W�̍ő�l
#define NONE 0		//�n�}��̉����Ȃ��Ƃ���
#define BLUE0 10
#define BLUE1 11
#define BLUE_FP 12
#define BLUE_RD 13
#define red0 20
#define red1 21
#define redfp 22
#define RED_RD 23

#define MAX_TURN 100 //�ő�^�[����

//xy���W��\���\����
struct position {
	int x;
	int y;
};

// �F���Ƃɐ��l���J�E���g���邽�߂̍\����
struct color {
	int blue;
	int red;
	int none;
};

// �}�b�v�̏�����
void init(void);

//���[�J����blue[]��red[]�����ł́C�Փ˂Ȃǂ̏�񂪂킩��Ȃ��B
//server�����map[][]�����ׂĂ̊�{�f�[�^�ɂȂ�B
//���̂��߁Cmap[][]����blue[]��red[]�̃f�[�^�𔲂��o���K�p������B
void get_agent_xy(void);

#endif