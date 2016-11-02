#ifndef TESTBARRETTSFIRSTATTEMPT_HPP_
#define TESTBARRETTSFIRSTATTEMPT_HPP_

// First, we include the necessary header files.
#include <cxxtest/TestSuite.h>
#include "CellBasedSimulationArchiver.hpp"
#include "SmartPointers.hpp"
#include "CylindricalHoneycombMeshGenerator.hpp"
#include "Cylindrical2dNodesOnlyMesh.hpp"
#include "CellsGenerator.hpp"
#include "NodeBasedCellPopulation.hpp"
#include "OffLatticeSimulation.hpp"
#include "RepulsionForce.hpp"
#include "PlaneBasedCellKiller.hpp"
#include "PlaneBoundaryCondition.hpp"
#include "AbstractCellBasedWithTimingsTestSuite.hpp"
#include "FakePetscSetup.hpp"

/**
 * \todo
 *
 * Initial condition: population of crypts at distal end of segment.
 *
 * Crypt fission rate: random time to divide.
 *
 * Flux in of young crypts at distal end of segment.
 *
 * Daughter cells acquire 'age' from ancestor crypt (either at division or an internal clock).
 *
 * Crypt death rate.
 *
 * Extract heatmap of tissue age.
 */

// This class defines the test suite
class TestBarrettsFirstAttempt : public AbstractCellBasedWithTimingsTestSuite
{
public:

    // This test defines a single simulation
    void TestBarrettsSimulation() throw (Exception)
    {
        // Specify the dimensions of the esophagus
        double esophagus_circumference = 10.0;
        double esophagus_length = 50.0;

        // Specify the simulation duration and time step
        double simulation_duration = 10.0

        // Create a mesh object with periodic left/right boundaries
        HoneycombMeshGenerator generator(esophagus_circumference, esophagus_length, 0);
        TetrahedralMesh<2,2>* p_generating_mesh = generator.GetMesh();
        Cylindrical2dNodesOnlyMesh* p_mesh = new Cylindrical2dNodesOnlyMesh(esophagus_circumference);
        p_mesh->ConstructNodesWithoutMesh(*p_generating_mesh, cut_off_length);

        // Create cells
        std::vector<CellPtr> cells;
        GenerateCells(p_mesh->GetNumNodes(), cells, M_PI*0.25,M_CONTACT_INHIBITION_LEVEL); // mature volume: M_PI*0.25 as r=0.5

        // Create a node-based cell population
        NodeBasedCellPopulation<2> cell_population(*p_mesh, cells);
        cell_population.AddCellWriter<CellAncestorWriter>();

        // Create simulation from cell population
        OffLatticeSimulation<2> simulator(cell_population);
        simulator.SetSamplingTimestepMultiple(120);
        simulator.SetEndTime(simulation_duration);
        simulator.SetOutputDirectory("BarrettsSimulation");

        // Create a 'repulsion' force law and pass it to the simulation
        MAKE_PTR(RepulsionForce<2>, p_force);
        simulator.AddForce(p_linear_force);

        // Impose a no-flux condition at the bottom boundary
        MAKE_PTR_ARGS(PlaneBoundaryCondition<2>, p_bcs, (&cell_population, zero_vector<double>(2), -unit_vector<double>(2,1)));
        simulator.AddCellPopulationBoundaryCondition(p_bcs);

        // Impose a 'sloughing' killer at the top boundary
        MAKE_PTR_ARGS(PlaneBasedCellKiller<2>, p_killer, (&cell_population, esophagus_length*unit_vector<double>(2,1), unit_vector<double>(2,1)));
        simulator.AddCellKiller(p_killer);

        // Run simulation
        simulator.Solve();
    }
};

#endif /* TESTBARRETTSFIRSTATTEMPT_HPP_ */
