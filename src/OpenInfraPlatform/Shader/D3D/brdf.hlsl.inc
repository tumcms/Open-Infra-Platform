/*
	Copyright (c) 2017 Technical University of Munich
	Chair of Computational Modeling and Simulation.

	TUM Open Infra Platform is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License Version 3
	as published by the Free Software Foundation.

	TUM Open Infra Platform is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

static const float PI = 3.14159265f;
static float3 lightColor = 0.7f;
static float3 lightDirection = float3(2, 4, 3);
static float3 ambientColor = 0.4f;
static bool camLight = false;

float GGX(float NdotV, float a)
{
    float k = a / 2;
    return NdotV / (NdotV * (1.0f - k) + k);
}

float G_Smith(float a, float nDotV, float nDotL)
{
    return GGX(nDotL, a * a) * GGX(nDotV, a * a);
}

float3 specularBRDF(float3 N, float3 V, float3 L, float3 color, float metallic, float ior, float roughness)
{
    float3 F0 = abs((1.0 - ior) / (1.0 + ior));
    F0 = F0 * F0;
    F0 = lerp(F0, color, metallic);

    float3 H = normalize(L + V);

    float NoV = max(saturate(dot(N, V)), 0.01f);
    float NoH = saturate(dot(N, H));
    float NoL = saturate(dot(N, L));
    float HoV = saturate(dot(H, V));

    if (NoL > 0)
    {
        float a = roughness;
        float a2 = a * a;

        float D = a2 / (PI * pow(pow(NoH, 2) * (a2 - 1) + 1, 2));
        float G = G_Smith(a, NoV, NoL);

        float3 F = F0 + (1 - F0) * pow(1 - HoV, 5);

        return G * D * F;
    }

    return 0;
}

float3 diffuseBRDF(float3 N, float3 V, float3 L, float3 color, float metallic, float ior)
{
    float3 F0 = abs((1.0 - ior) / (1.0 + ior));
    F0 = F0 * F0;
    F0 = lerp(F0, color, metallic);

    float3 H = normalize(L + V);

    float NoL = saturate(dot(N, L));
    float NoH = saturate(dot(N, H));
    float HoV = saturate(dot(H, V));

    if (NoL > 0)
    {
        float3 F = F0 + (1 - F0) * pow(1 - HoV, 5);
        return color * NoL * (1 - F);
    }

    return 0;
}


float3 brdf(float3 cam, float3 P, float3 N, float3 color, float metallic, float roughness, float ior)
{
    float3 result = 0;

    float3 V = normalize(cam - P);

    float3 L = normalize(lightDirection);
    if (camLight)
        L = V;

    float3 direct = 0;
    direct += specularBRDF(N, V, L, color, metallic, ior, roughness);
    direct += diffuseBRDF(N, V, L, color, metallic, ior);
    direct *= lightColor;

    float3 ambient = 0;
    ambient += diffuseBRDF(N, V, N, color, metallic, ior);
    ambient *= ambientColor;

    result = direct + ambient;

    return result;
}

//void main(){}