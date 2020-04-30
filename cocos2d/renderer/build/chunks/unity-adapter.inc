
  ////////////////////////////////
  // unity tools include

  #define float4 vec4
  #define float3 vec3
  #define float2 vec2

  #define fixed4 vec4
  #define fixed2 vec3
  #define fixed2 vec2

  #define float2x2 mat2
  #define float3x3 mat3

  #define unity_ObjectToWorld cc_matWorld
  #define unity_WorldToObject cc_matWorldIT

  #define UNITY_MATRIX_VP cc_matViewProj
  #define UNITY_MATRIX_V cc_matView
  #define _Time cc_time

  //x is 1.0 (or –1.0 if currently rendering with a flipped projection matrix), y is the camera’s near plane, z is the camera’s far plane and w is 1/FarPlane.
  const float4 _ProjectionParams = float4(1.0, 20.0, 100.0, 0.0166667);
  //Used to linearize Z buffer values. x is (1-far/near), y is (far/near), z is (x/far) and w is (y/far).
  const float4 _ZBufferParams = float4(-4.0, 5.0, -0.04, 0.05);

  vec3 pow3(vec3 d, float p)
  {
    return pow(d, vec3(p));
  }

  float maxi(float a, float b)
  {
    return max(a, b);
  }

  float maxi(int a, float b)
  {
    return max(float(a), b);
  }

  vec4 mul( mat4 mat, vec4 vector )
  {
    return mat * vector;
  }
  vec2 mul( mat2 mat, vec2 vector )
  {
    return mat * vector;
  }
  vec2 mul( vec2 vector, mat2 mat )
  {
    return vector * mat;
  }
  vec3 mul( vec3 vector, mat3 mat )
  {
    return vector * mat;
  }
  vec3 mul( mat3 mat, vec3 vector )
  {
    return mat * vector;
  }

  void clip(float a)
  {
    if(a < 0.0) discard;
  }

  float4 UnityObjectToClipPos(in float3 pos)
  {
      return UNITY_MATRIX_VP * unity_ObjectToWorld * float4(pos,1.0);
  }

  float4 UnityObjectToClipPos(float4 pos)
  {
      return UNITY_MATRIX_VP * unity_ObjectToWorld * pos;
  }

  vec3 UnityObjectToWorldNormal(vec3 normal){
    return normalize((cc_matWorldIT * vec4(normal, 0)).xyz);
  }

  float4 ComputeNonStereoScreenPos(float4 pos) {
      float4 o = pos * 0.5;
      o.xy = float2(o.x, o.y*1.0) + o.w;
      o.zw = pos.zw;
      return o;
  }

  float4 ComputeScreenPos(float4 pos) {
      float4 o = ComputeNonStereoScreenPos(pos);
      return o;
  }

  // Z buffer to linear 0..1 depth
  float Linear01Depth( float z )
  {
      return 1.0 / (_ZBufferParams.x * z + _ZBufferParams.y);
  }
  // Z buffer to linear depth
  float LinearEyeDepth( float z )
  {
      return 1.0 / (_ZBufferParams.z * z + _ZBufferParams.w);
  }

  float3 UnityObjectToViewPos( in float3 pos )
  {
      return mul(UNITY_MATRIX_V, mul(unity_ObjectToWorld, float4(pos, 1.0))).xyz;
  }
  float3 UnityObjectToViewPos( in float4 pos )
  {
      return mul(UNITY_MATRIX_V, mul(unity_ObjectToWorld, float4(pos.xyz, 1.0))).xyz;
  }
  #define COMPUTE_EYEDEPTH(v,o) o = -UnityObjectToViewPos( v.vertex ).z

  #define LIGHT_ATTENUATION(i) CCCalcShadow()

  float DecodeFloatRGBA(highp vec4 enc){
    highp vec4 kDecodeDot = vec4(1.0,1.0/255.0,1.0/65025.0,1.0/160581375.0);
    return dot(enc, kDecodeDot);
  }

  #define TRANSFORM_TEX(tex,name) (tex.xy * name##_ST.xy + name##_ST.zw)
  #define tex2D texture2D
  #define lerp mix
  #define tex2Dproj texture2DProj

  #define _WorldSpaceLightPos0 -cc_dirLightDirection[0]
  #define _LightColor0 cc_dirLightColor[0]
  #define _WorldSpaceCameraPos cc_cameraPos

  #define frac fract


