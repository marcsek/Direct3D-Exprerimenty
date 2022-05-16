cbuffer LightCBuf
{
    float3 lightPos;
    float3 ambient;
    float3 diffuseColor;
    float diffuseIntensity;
    float attConst;
    float attLin;
    float attQuad;
};

cbuffer ObjectCBuf
{
    float3 materialColor[6];
    float padding; //!!!!!!
    float specularIntensity;
    float specularPower;
};

float4 main(float3 worldPos : POSITION, float3 n : NORMAL, uint tid : SV_PrimitiveID) : SV_TARGET
{
    const float3 vTol = lightPos - worldPos;
    const float distTol = length(vTol);
    const float3 dirTol = vTol / distTol;
    
    const float att = 1.0f / (attConst + attLin * distTol + attQuad * (distTol * distTol));
    
    const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirTol, n));
    
    const float3 w = n * dot(vTol, n);
    const float3 r = w * 2.0f - vTol;
    
    const float3 specular = att * (diffuseColor * diffuseIntensity) * specularIntensity * pow(max(0.0f, dot(normalize(-r), normalize(worldPos))), specularPower);
    
    return float4(saturate((diffuse + ambient + specular) * materialColor[tid % 6]), 1.0f);
}