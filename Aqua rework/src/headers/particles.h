#pragma once

struct Particle
{
    ImVec2 position;
    ImVec2 velocity;
    float size;
    ImU32 color;
};

std::vector<Particle> particles;
const int MAX_PARTICLES = 120; 

void InitializeParticles()
{
    
}

void UpdateParticles(float deltaTime)
{
   
    while (particles.size() < MAX_PARTICLES)
    {
        Particle particle;
        particle.position = ImVec2(rand() % 700, 475); 
        particle.velocity = ImVec2((rand() % 30 - 15) / 10.0f, -(rand() % 50 / 100.0f + 0.5f)); 
        particle.size = (rand() % 3 + 1) * 0.5f; // die grösser der komischen kugeln habe cih zwei drinne also zwei unterschiedliche 
        particle.color = IM_COL32(255, 69, 0, 255); // Startfarbe: Feuer-Orange
        particles.push_back(particle);
    }

   
    for (int i = 0; i < particles.size(); ++i)
    {
        
        particles[i].position.x += particles[i].velocity.x * deltaTime * 60.0f; // Horizontal
        particles[i].position.y += particles[i].velocity.y * deltaTime * 100.0f; // Vertikal

        
        if (particles[i].position.y < 0)
        {
            particles[i].position.y = 475;
            particles[i].position.x = rand() % 700; 
        }

        
        int r = 255; 
        int g = 69;  
        int b = 0;   
        particles[i].color = IM_COL32(r, g, b, 255); 
    }
}

void RenderParticles()
{
    for (int i = 0; i < particles.size(); ++i)
    {
        ImGui::GetWindowDrawList()->AddCircleFilled(particles[i].position, particles[i].size, particles[i].color);
    }
}
