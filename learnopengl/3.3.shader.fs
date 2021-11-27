#version 330 core
out vec4 FragColor;  
//in vec3 ourColor;
//in vec2 TexCoord;

uniform sampler2D texture1;//内建数据类型，纹理采样器
uniform sampler2D texture2;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
void main()
{
   //FragColor = vec4(ourColor, 1.0);
   // FragColor = texture(texture1, TexCoord);//内建函数
   // FragColor = texture(texture1, TexCoord)*vec4(ourColor,1.0);
   FragColor = mix(texture(texture1, TexCoord),texture(texture2, TexCoord),0.2);//20%的texture2
 
}