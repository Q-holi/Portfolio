
struct VertexInput
{
	float4 position : POSITION0; //�뵵
    float4 color : COLOR0;
};
// PI
struct PixelInput
{
    float4 position : SV_POSITION; //ȭ����ǥ�� ������
    float4 color : COLOR0;
};

//������Ʈ�� ũ�� ȸ�� �̵�
cbuffer VS_WVP : register(b0) //register(b0)
{
    matrix WVP;
}
cbuffer VS_COLOR : register(b1)
{
    //4 ���� 4����Ʈ
    float4 color;
}



PixelInput VS(VertexInput input)
{
    //������ȯ�� ���� ������ ��
    PixelInput output;
    
    output.position = mul(input.position, WVP);
	output.color = input.color + (color * 2.0f - 1.0f);
	saturate(output.color);
    
	return output;
}
//->pixel  PS   ->color
//�ȼ����̴� ���� �Լ�
float4 PS(PixelInput input) : SV_TARGET //SV_TARGET �� Ÿ���̵� ���� 
{
    //����Ʈ���� ��ȯ�� ��������
    //��ũ����ǥ
    
	float4 OutputColor;
	OutputColor = saturate(input.color);
    
	return OutputColor;
}