#ifndef GLSLSOURCEHYBRIDMULTIFRACTAL_HPP
#define GLSLSOURCEHYBRIDMULTIFRACTAL_HPP

constexpr const char * source_hybridmultifractal = R"lobotomized(

//depends on snoise
float hybridmultifractal(vec2 pos, float octaves, float lacunarity, float h, float offset){
    //compute first octave
    float result = snoise(pos) + offset;
    float weight = result;
    float frequency = lacunarity;

    for(int i=1; i<octaves; ++i) {
        //prevent divergence
        weight = min(weight, 1.0f);

        //get next higher frequency
        float exponent = pow(pow(lacunarity, i), -h); //these may perhaps be precomputed
        float signal = (snoise(pos*frequency) + offset) * exponent;
        //add it in, weighted by previous freq's local value
        result += weight * signal;
        //update the (monotonically decreasing) weighting value
        //(this is why H must specify a high fractal dimension)
        weight *= signal;

        //increase frequency
        frequency *= lacunarity;
    }
/*
    //take care of remainder in ``octaves''
    float remainder = octaves - floor(octaves);
    if(remainder>0){
        //spatial freq. is preset in loop above
        float exponent = pow(pow(lacunarity, octaves), -h);
        result += remainder * snoise(pos*frequency) * exponent;
    }
    */

    return result;
}

)lobotomized";

#endif // GLSLSOURCEHYBRIDMULTIFRACTAL_HPP
