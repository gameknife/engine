uniform SKY_GI {
  vec4 skyGIParam;
  vec4 skyGIColor;
};
uniform sampler2D skyTexture;

vec3 calcSkyLight( vec3 worldpos, vec3 normal )
{
  // GI-skylight
  vec2 uv = (worldpos.xz + vec2(skyGIParam.x * 0.5 + 1.0,skyGIParam.y - 1.0 - skyGIParam.w)) * vec2(1.0 / (skyGIParam.x + 1.0), 1.0 / (skyGIParam.y - 1.0));
  uv.y = 1.0 - uv.y;

  vec3 skycolor = texture2D(skyTexture, uv).rgb;
  skycolor = mix(skycolor, skyGIColor.rgb, min(worldpos.y * skyGIParam.z, 1.0));

  // 再根据normaly混合一个顶底明暗
  float topdownsky = normal.y * 0.5 + 0.5;
  topdownsky = topdownsky * 0.25 + 0.75;
  skycolor *= topdownsky;

  return skycolor;
}

vec4 finalComposite( vec3 skyColor, vec3 allLight, vec3 albedo, vec3 finalOutput)
{
  #if USE_DEBUG_VISUAL == 1
  return vec4(albedo,1.0);
  #elif USE_DEBUG_VISUAL == 2 
  return vec4(skyColor,1.0);
  #elif USE_DEBUG_VISUAL == 3
  return vec4(allLight,1.0);
  #else
  return vec4(finalOutput*0.5,1.0);
  #endif
}
