//210430�� ���̴� 2��°�ð�.
//��� �ֱ�(�ͷ��ο���) �ٵ� ���� �ͷ��� �Ⱦ��ϲ�
//�ٷ� �Ž� ���鼭 �����غ���.

//�ؽ��� ���� ������̺��� �Ȱ���.
matrix		g_matWorld;
matrix		g_matView;
matrix		g_matProjection;

texture		g_texBaseTexture;

sampler BaseSampler = sampler_state
{
	texture = g_texBaseTexture;

	minfilter = linear;
	magfilter = linear;
};

//��Ͽ��� �ʿ��� ��� ���̺��
/* �� */
	//1. ����
	//2. ��ǻ�� (���ݻ�)
	//3. ����ŧ�� (���ݻ�)
		//=> power�� : ����ŧ���� �ִ���ּ�ġ�� ������ �������ֱ� ���ؼ� ��. �������༭.
	//4. �����Ʈ
	

/* ���׸��� */
	//1. ��ǻ��
	//2. ����ŧ��
	//3. �����Ʈ

