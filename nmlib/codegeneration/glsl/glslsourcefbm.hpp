#ifndef GLSLSOURCEFBM_HPP
#define GLSLSOURCEFBM_HPP

constexpr const char * source_fbm2d = R"lobotomized(

//depends on snoise
float fbm2d(vec2 pos, float octaves, float lacunarity, float gain) {
    float sum = 0;
    float amplitude = 1;
    float frequency = 1;
    for(int i=0; i<octaves; ++i){
        sum += snoise(pos*frequency)*amplitude;
        amplitude *= gain;
        frequency *= lacunarity;
    }
    return sum;
}

)lobotomized";

#endif // GLSLSOURCEFBM_HPP
