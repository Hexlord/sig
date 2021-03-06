//
// Generated with SIG genpredefinedshaders.py - (c) Marcelo Kallmann 2016-2020
//

static const char* pds_spm_cone_frag=
"#version 430\n"
"in vec4 vert_Color;"
"out vec4 frag_Color;"
"layout(std430,binding=0)buffer VertexData\n"
"{"
"vec4 Vert[];"
"};"
"uniform sampler2DRect texId,drawId;"
"uniform ivec2 window;"
"uniform mat4 projectionMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 modelMatrix;"
"void main(void)"
"{"
"vec4 tex_value=texelFetch(texId,ivec2(gl_FragCoord.xy));"
"vec4 draw_value=texelFetch(drawId,ivec2(gl_FragCoord.xy));"
"frag_Color=draw_value;"
"if(tex_value.w !=0.0)"
"return;"
"vec2 spos=vec2(float(gl_FragCoord.x)/float(window.x),float(gl_FragCoord.y)/float(window.y));"
"vec2 parent;"
"vec4 gen0=projectionMatrix*viewMatrix*modelMatrix*vec4(Vert[0].xy,0.0,1.0);"
"vec4 gen1=projectionMatrix*viewMatrix*modelMatrix*vec4(Vert[1].xy,0.0,1.0);"
"vec2 sgen0=(gen0.xy + 1.0)/2.0;"
"vec2 sgen1=(gen1.xy + 1.0)/2.0;"
"if(Vert[0].w==2.0)"
"{"
"float len=length(sgen1 - sgen0)*length(sgen1 - sgen0);"
"if(len==0.0)"
"parent=sgen0;"
"else\n"
"{"
"float d=dot(spos - sgen0,sgen1 - sgen0)/len;"
"if(d < 0.0)"
"parent=sgen0;"
"else if(d > 1.0)"
"parent=sgen1;"
"else\n"
"parent=sgen0 + d*(sgen1 - sgen0);"
"}"
"}"
"else\n"
"parent=sgen1;"
"float dist=distance(spos,parent);"
"float depth=(dist*Vert[1].z)+ Vert[0].z;"
"if(draw_value.w==0.0 || depth < draw_value.z){"
"if(Vert[1].z !=1.0)"
"frag_Color=vec4(parent.xy,depth,1.1);"
"else\n"
"frag_Color=vec4(parent.xy,depth,1.0);"
"}"
"}"
;
static const char* pds_spm_cone_vert=
"#version 430\n"
"layout(location=0)in vec4 in_Position;"
"layout(location=1)in vec4 in_Color;"
"out vec4 vert_Color;"
"void main(void)"
"{"
"gl_Position=in_Position;"
"vert_Color=in_Color;"
"}"
;
static const char* pds_spm_distance_comp=
"#version 430\n"
"layout(local_size_x=1)in;"
"layout(std430,binding=0)buffer VertexData\n"
"{"
"vec4 Vert[];"
"};"
"uniform sampler2DRect texId;"
"uniform ivec2 window;"
"uniform bool prec;"
"uniform int arrayLeap;"
"uniform int numLeaps;"
"uniform mat4 projectionMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 modelMatrix;"
"void main()"
"{"
"int id=(int(gl_GlobalInvocationID.x)+ 1)*2;"
"if(Vert[id].w !=1.0)"
"return;"
"vec4 posp=projectionMatrix*viewMatrix*modelMatrix*vec4(Vert[id ].xy,0.0,1.0);"
"vec4 poso=projectionMatrix*viewMatrix*modelMatrix*vec4(Vert[id+1].xy,0.0,1.0);"
"vec2 sposp=(posp.xy + 1.0)/2.0;"
"vec2 sposo=(poso.xy + 1.0)/2.0;"
"vec4 gen0=projectionMatrix*viewMatrix*modelMatrix*vec4(Vert[0].xy,0.0,1.0);"
"vec4 gen1=projectionMatrix*viewMatrix*modelMatrix*vec4(Vert[1].xy,0.0,1.0);"
"vec2 sgen0=(gen0.xy + 1.0)/2.0;"
"vec2 sgen1=(gen1.xy + 1.0)/2.0;"
"float dist;"
"if(Vert[0].w==2.0)"
"{"
"float len=length(sgen1 - sgen0)*length(sgen1 - sgen0);"
"if(len==0.0)"
"dist=distance(sposo.xy,sgen0.xy);"
"else\n"
"{"
"float d=dot(sposo - sgen0,sgen1 - sgen0)/len;"
"if(d < 0.0)"
"dist=distance(sposo,sgen0);"
"else if(d > 1.0)"
"dist=distance(sposo,sgen1);"
"else\n"
"{"
"vec2 proj=sgen0 + d*(sgen1 - sgen0);"
"dist=distance(sposo,proj);"
"}"
"}"
"}"
"else\n"
"dist=distance(sposo.xy,sgen1.xy);"
"float depth=(dist*Vert[1].z)+ Vert[0].z;"
"ivec2 frag=ivec2(sposp.x*window.x,sposp.y*window.y);"
"vec4 tex_value;"
"vec4 tex_value0,tex_value1,tex_value2,tex_value3;"
"if(prec==false)"
"{"
"tex_value=texelFetch(texId,ivec2(frag.xy));"
"}"
"else\n"
"{"
"ivec2 frag0=ivec2(frag.x + 1,frag.y + 1);"
"ivec2 frag1=ivec2(frag.x - 1,frag.y + 1);"
"ivec2 frag2=ivec2(frag.x + 1,frag.y - 1);"
"ivec2 frag3=ivec2(frag.x - 1,frag.y - 1);"
"tex_value0=texelFetch(texId,ivec2(frag0.xy));"
"tex_value1=texelFetch(texId,ivec2(frag1.xy));"
"tex_value2=texelFetch(texId,ivec2(frag2.xy));"
"tex_value3=texelFetch(texId,ivec2(frag3.xy));"
"}"
"if((prec==false && tex_value.w==0.0)||\n"
"(prec==true &&(tex_value0.w==0.0 || tex_value1.w==0.0 || tex_value2.w==0.0 || tex_value3.w==0.0)))"
"{"
"if(Vert[id].z==0.0 || depth < Vert[id].z)"
"{"
"Vert[id ].z=depth;"
"Vert[id+1].w=Vert[1].w;"
"if(Vert[id+1].z > Vert[1].z)"
"Vert[id+1].z=Vert[1].z;"
"}"
"else\n"
"{"
"for(int i=1; i <=numLeaps; ++i)"
"{"
"int jumpID=id +(arrayLeap*i);"
"if(Vert[ jumpID + 1 ].z==Vert[1].z)"
"{"
"if(Vert[ jumpID ].z==0.0 || depth < Vert[ jumpID ].z)"
"{"
"Vert[ jumpID   ].z=depth;"
"Vert[ jumpID   ].w=1.0;"
"Vert[ jumpID + 1 ].w=Vert[1].w;"
"}"
"}"
"}"
"}"
"/*else if(Vert[id+33].z==Vert[1].z)"
"{"
"if(Vert[id+32].z==0.0 || depth < Vert[id+32].z)"
"{"
"Vert[id+32].z=depth;"
"Vert[id+32].w=1.0;"
"Vert[id+33].w=Vert[1].w;"
"}"
"}*/\n"
"}"
"}"
;
static const char* pds_spm_draw_frag=
"#version 430\n"
"in vec3 TexCoord;"
"uniform ivec2 bufferDim;"
"uniform sampler2DRect drawTexId;"
"uniform bool contourLines;"
"uniform float contourInterval;"
"uniform float contourThickness;"
"uniform bool distanceField;"
"out vec4 frag_Color;"
"void main()"
"{"
"ivec2 frag_TexCoord=ivec2(bufferDim.x*TexCoord.x,bufferDim.y*TexCoord.y);"
"frag_Color=texelFetch(drawTexId,frag_TexCoord);"
"if(frag_Color.w==0.0)"
"discard;"
"if(contourLines==true && mod(abs(frag_Color.z),contourInterval)<=contourThickness){"
"frag_Color=vec4(1.0);"
"return;"
"}"
"if(distanceField==true && frag_Color !=vec4(1.0)){"
"double d=abs(frag_Color.z);"
"frag_Color=vec4(d,1.0-d,0.0,1.0);"
"return;"
"}"
"if(frag_Color !=vec4(1.0))"
"frag_Color.z=0.0;"
"}"
;
static const char* pds_spm_draw_vert=
"#version 430\n"
"layout(location=0)in vec3 vPos;"
"layout(location=1)in vec3 vTex;"
"uniform mat4 vProj;"
"uniform mat4 vView;"
"out vec3 TexCoord;"
"void main()"
"{"
"gl_Position=vec4(vPos.x,vPos.y,vPos.z,1.0)*vView*vProj;"
"TexCoord=vTex;"
"}"
;
static const char* pds_spm_search_comp=
"#version 430\n"
"layout(local_size_x=1)in;"
"layout(std430,binding=0)buffer VertexData\n"
"{"
"vec4 Vert[];"
"};"
"void main()"
"{"
"int minIdx=-1;"
"float minDist=-1.0;"
"int i=4;"
"while(Vert[i].w !=0.0)"
"{"
"if(Vert[i].w >=1.5)"
"{"
"minIdx=i;"
"minDist=Vert[i].z;"
"break;"
"}"
"else if(Vert[i].w==1.0)"
"{"
"if(Vert[i].z > 0.0 &&(minIdx==-1 || Vert[i].z < minDist))"
"{"
"minIdx=i;"
"minDist=Vert[i].z;"
"}"
"}"
"i=i + 2;"
"}"
"if(minIdx !=-1)"
"{"
"Vert[0]=Vert[ minIdx  ];"
"Vert[1]=Vert[ minIdx+1 ];"
"Vert[1].w=minIdx/2-1;"
"Vert[ minIdx ].w=0.5;"
"}"
"}"
;
static const char* pds_spm_shadow_frag=
"#version 430\n"
"in vec4 geom_Color;"
"out vec4 frag_Color;"
"void main(void)"
"{"
"frag_Color=geom_Color;"
"}"
;
static const char* pds_spm_shadow_geom=
"#version 430\n"
"layout(lines)in;"
"layout(triangle_strip,max_vertices=18)out;"
"in vec4 vert_Color[2];"
"out vec4 geom_Color;"
"layout(std430,binding=0)buffer VertexData\n"
"{"
"vec4 Vert[];"
"};"
"uniform mat4 projectionMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 modelMatrix;"
"void main(void)"
"{"
"vec4 pos0=projectionMatrix*viewMatrix*modelMatrix*vec4(gl_in[0].gl_Position.xy,0.0,1.0);"
"vec4 pos1=projectionMatrix*viewMatrix*modelMatrix*vec4(gl_in[1].gl_Position.xy,0.0,1.0);"
"vec4 posm=(pos0 + pos1)/2.0;"
"float dx=pos1.x - pos0.x;"
"float dy=pos1.y - pos0.y;"
"{"
"vec4 poss=projectionMatrix*viewMatrix*modelMatrix*vec4(Vert[0].xy,0.0,1.0);"
"vec4 n1=normalize(vec4(dy,-dx,0.0,0.0));"
"vec4 n0s=normalize(pos0 - poss);"
"vec4 n1s=normalize(pos1 - poss);"
"vec4 n =normalize(posm - poss);"
"vec4 nm=normalize(n0s + n1s);"
"vec4 pos0s=pos0 +(n0s*4.0);"
"vec4 pos1s=pos1 +(n1s*4.0);"
"vec4 posms=posm +(nm*4.0);"
"float d=dot(n,n1);"
"{"
"geom_Color=vec4(0.0,0.0,0.0,1.0);"
"gl_Position=pos0;"
"EmitVertex();"
"gl_Position=posms;"
"EmitVertex();"
"gl_Position=pos0s;"
"EmitVertex();"
"EndPrimitive();"
"gl_Position=pos1;"
"EmitVertex();"
"gl_Position=pos1s;"
"EmitVertex();"
"gl_Position=posms;"
"EmitVertex();"
"EndPrimitive();"
"gl_Position=pos0;"
"EmitVertex();"
"gl_Position=pos1;"
"EmitVertex();"
"gl_Position=posms;"
"EmitVertex();"
"EndPrimitive();"
"}"
"}"
"if(Vert[0].w==2.0)"
"{"
"vec4 poss=projectionMatrix*viewMatrix*modelMatrix*vec4(Vert[1].xy,0.0,1.0);"
"vec4 n1=normalize(vec4(dy,-dx,0.0,0.0));"
"vec4 n0s=normalize(pos0 - poss);"
"vec4 n1s=normalize(pos1 - poss);"
"vec4 n =normalize(posm - poss);"
"vec4 nm=normalize(n0s + n1s);"
"vec4 pos0s=pos0 +(n0s*4.0);"
"vec4 pos1s=pos1 +(n1s*4.0);"
"vec4 posms=posm +(nm*4.0);"
"float d=dot(n,n1);"
"{"
"geom_Color=vec4(0.0,0.0,0.0,1.0);"
"gl_Position=pos0;"
"EmitVertex();"
"gl_Position=posms;"
"EmitVertex();"
"gl_Position=pos0s;"
"EmitVertex();"
"EndPrimitive();"
"gl_Position=pos1;"
"EmitVertex();"
"gl_Position=pos1s;"
"EmitVertex();"
"gl_Position=posms;"
"EmitVertex();"
"EndPrimitive();"
"gl_Position=pos0;"
"EmitVertex();"
"gl_Position=pos1;"
"EmitVertex();"
"gl_Position=posms;"
"EmitVertex();"
"EndPrimitive();"
"}"
"}"
"}"
;
static const char* pds_spm_shadow_vert=
"#version 430\n"
"layout(location=0)in vec4 in_Position;"
"layout(location=1)in vec4 in_Color;"
"out vec4 vert_Color;"
"void main(void)"
"{"
"gl_Position=in_Position;"
"vert_Color=in_Color;"
"}"
;
