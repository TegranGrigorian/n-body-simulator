import nbody

# Create Sun and Earth
sun = nbody.Body(1.989e30, 0.0, 0.0, 0.0, 0.0)
earth = nbody.Body(5.972e24, nbody.AU, 0.0, 0.0, 29780.0)

# Create simulation
sim = nbody.Kosmos([sun, earth])

# Run for 1 day
for _ in range(24):
    sim.step(3600.0)  # 1 hour steps

# Check positions
bodies = sim.get_bodies()
print(f"Earth: x={bodies[1].get_x():.3e}, y={bodies[1].get_y():.3e}")