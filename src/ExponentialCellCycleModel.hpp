#ifndef EXPONENTIALCELLCYCLEMODEL_HPP_
#define EXPONENTIALCELLCYCLEMODEL_HPP_

#include "AbstractSimpleCellCycleModel.hpp"
#include "RandomNumberGenerator.hpp"

class ExponentialCellCycleModel : public AbstractSimpleCellCycleModel
{
private:

    /**
     * The average cell cycle rate.
     * Defaults to 1 per time unit.
     */
    double mRate;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & archive, const unsigned int version)
    {
        archive & boost::serialization::base_object<AbstractSimpleCellCycleModel>(*this);

        // Make sure the RandomNumberGenerator singleton gets saved too
        SerializableSingleton<RandomNumberGenerator>* p_wrapper = RandomNumberGenerator::Instance()->GetSerializationWrapper();
        archive & p_wrapper;
        archive & mRate;
    }

protected:

    /**
     * Protected copy-constructor for use by CreateCellCycleModel().
     *
     * The only way for external code to create a copy of a cell cycle model
     * is by calling that method, to ensure that a model of the correct subclass is created.
     * This copy-constructor helps subclasses to ensure that all member variables are correctly copied when this happens.
     *
     * This method is called by child classes to set member variables for a daughter cell upon cell division.
     * Note that the parent cell cycle model will have had ResetForDivision() called just before CreateCellCycleModel() is called,
     * so performing an exact copy of the parent is suitable behaviour. Any daughter-cell-specific initialisation
     * can be done in InitialiseDaughterCell().
     *
     * @param rModel the cell cycle model to copy.
     */
    ExponentialCellCycleModel(const ExponentialCellCycleModel& rModel);

public:

    /**
     * Constructor - just a default, mBirthTime is set in the AbstractCellCycleModel class.
     * mG1Duration is set very high, it is set for the individual cells when InitialiseDaughterCell is called
     */
    ExponentialCellCycleModel();

    /**
     * Overridden SetCellCycleDuration() method to add stochastic cell cycle times.
     */
    void SetCellCycleDuration();

    /**
     * Overridden builder method to create new copies of
     * this cell-cycle model.
     *
     * @return new cell-cycle model
     */
    AbstractCellCycleModel* CreateCellCycleModel();

    /**
     * Set mRate.
     */
    void SetRate(double meanCycleDuration);

    /**
     * Overridden (but unused) GetAverageTransitCellCycleTime() method.
     *
     * Note: Although it is not used, this method must be overridden in
     * any subclass of AbstractCellCycleModel, since it is pure virtual
     * in that class.
     *
     * @return the average of mMinCellCycleDuration and mMaxCellCycleDuration
     */
    double GetAverageTransitCellCycleTime();

    /**
     * Overridden (but unused) GetAverageStemCellCycleTime() method.
     *
     * Note: Although it is not used, this method must be overridden in
     * any subclass of AbstractCellCycleModel, since it is pure virtual
     * in that class.
     *
     * @return the average of mMinCellCycleDuration and mMaxCellCycleDuration
     */
    double GetAverageStemCellCycleTime();

    /**
     * Overridden OutputCellCycleModelParameters() method.
     *
     * Note: Although it is not used, this method must be overridden in
     * any subclass of AbstractCellCycleModel, since it is pure virtual
     * in that class.
     *
     * @param rParamsFile the file stream to which the parameters are output
     */
    virtual void OutputCellCycleModelParameters(out_stream& rParamsFile);
};

#include "SerializationExportWrapper.hpp"
// Declare identifier for the serializer
CHASTE_CLASS_EXPORT(ExponentialCellCycleModel)

#endif /*EXPONENTIALCELLCYCLEMODEL_HPP_*/
