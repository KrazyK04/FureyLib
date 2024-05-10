
// Flow Data Particles Script
// by Kyle Furey for NASA VR Project

using UnityEngine;

/// <summary>
/// Creates particles and controls their visibility to accurately represent the flow data.
/// </summary>
[RequireComponent(typeof(ParticleSystem))]
public class ParticleVisibility : MonoBehaviour
{
    [Header("Creates particles and controls their visibility to accurately represent the flow data.")]

    [Header("The file containing the data for the particles to represent:")]
    [SerializeField] private FlowFile flowFile;

    /// <summary>
    /// Particle system variables
    /// </summary>
    private ParticleSystem particleSystem;
    private ParticleSystem.Particle[] particles;

    [Header("Whether the bounds and origin for the particle system are static and do not change:")]
    public bool boundsAreStatic = true;

    [Header("The scale of the bounds for where particles may go:")]
    public Vector3 particleBounds = Vector3.one;

    [Header("The relative origin of the particle system:")]
    public Vector3 particleOrigin = new Vector3(0.5f, 0.5f, 0.5f);

    /// <summary>
    /// The scale of a particle's position
    /// </summary>
    public const float particleScale = 100;

    /// <summary>
    /// The flow data cube's collider
    /// </summary>
    private BoxCollider collider = null;

    /// <summary>
    /// Sets particle system variables
    /// </summary>
    private void Awake()
    {
        // Gets the particle system
        particleSystem = GetComponent<ParticleSystem>();

        particles = new ParticleSystem.Particle[particleSystem.main.maxParticles];

        // Check for a collider
        if (collider == null)
        {
            collider = gameObject.AddComponent<BoxCollider>();
        }

        // Update the collider's trigger
        collider.isTrigger = true;

        // Update the collider's size
        collider.size = particleBounds;
    }

    /// <summary>
    /// Called every frame
    /// </summary>
    private void Update()
    {
        if (!boundsAreStatic)
        {
            // Update the collider's trigger
            collider.isTrigger = true;

            // Update the collider's size
            collider.size = particleBounds;
        }

        // PARTICLE SYSTEM UPDATE -> CAMERA RENDER -> UPDATE PARTICLE

        // Updates the particles every frame (renders after the camera, causes flickering!)
        //UpdateParticle();
    }

    /// <summary>
    /// Called when the particle system itself updates
    /// </summary>
    private void OnParticleUpdateJobScheduled()
    {
        // PARTICLE SYSTEM UPDATE -> UPDATE PARTICLE -> CAMERA RENDER

        // Let the particle system update itself, but manually update the particles immediately after with an invoke call.
        // This ensures the particles are updated before the camera renders them (to prevent flickering).
        Invoke("UpdateParticle", 0);
    }

    /// <summary>
    /// Updates the particles
    /// </summary>
    private void UpdateParticle()
    {
        // Store the number of particles remaining
        int totalParticlesAlive = particleSystem.GetParticles(particles);

        // Loop through each particle
        for (int i = 0; i < totalParticlesAlive; ++i)
        {
            // OLD BOUNDS CHECK
            // if (flowFile.InBounds(particles[i].position))

            // Check if the particles are in the bounds of the set
            if (ParticleInBounds(particles[i].position))
            {
                // Update the particle's velocity
                particles[i].velocity = flowFile.Sample(particles[i].position);
            }
            else
            {
                // Remove the particle
                particles[i].remainingLifetime = -1f;
            }
        }

        // Update the number of particles
        particleSystem.SetParticles(particles, totalParticlesAlive);
    }

    /// <summary>
    /// Determine if the position of a particle is in bounds of the scaled set
    /// </summary>
    /// <param name="particlePosition"></param>
    /// <returns></returns>
    private bool ParticleInBounds(Vector3 particlePosition)
    {
        return (particlePosition.x / particleScale >= particleOrigin.x - particleBounds.x / 2) && (particlePosition.x / particleScale <= particleOrigin.x + particleBounds.x / 2) &&
               (particlePosition.y / particleScale >= particleOrigin.y - particleBounds.y / 2) && (particlePosition.y / particleScale <= particleOrigin.y + particleBounds.y / 2) &&
               (particlePosition.z / particleScale >= particleOrigin.z - particleBounds.z / 2) && (particlePosition.z / particleScale <= particleOrigin.z + particleBounds.z / 2);
    }
}
