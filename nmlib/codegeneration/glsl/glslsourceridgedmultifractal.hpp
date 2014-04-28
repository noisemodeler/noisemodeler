#ifndef GLSLSOURCERIDGEDMULTIFRACTAL_HPP
#define GLSLSOURCERIDGEDMULTIFRACTAL_HPP

constexpr const char * source_ridgedmultifractal = R"lobotomized(

//depends on snoise
float ridgedmultifractal(vec2 pos, float octaves, float lacunarity, float h, float offset, float gain){

    //compute first octave
    float signal = snoise(pos);
    signal = abs(signal);
    signal = offset - signal;
    signal *= signal;

    float result = signal;
    float frequency = lacunarity;
    float weight = 1;

    for(int i=1; weight>0.001f && i<octaves; ++i){ //TODO get rid of magic constant
        weight = signal*gain;
        weight = clamp(weight, 0, 1);
        signal = snoise(pos*frequency);
        signal = abs(signal);
        signal = offset - signal;
        signal *= signal;
        signal *= weight;

        float exponent = pow(pow(lacunarity, i), -h);
        result += signal * exponent;
        weight *=  signal; // update the monotonically decreasing weight

        frequency *= lacunarity;
    }
    return result;
}

)lobotomized";

#endif // GLSLSOURCERIDGEDMULTIFRACTAL_HPP
