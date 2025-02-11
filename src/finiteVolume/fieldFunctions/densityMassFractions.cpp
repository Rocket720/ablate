#include "densityMassFractions.hpp"

ablate::finiteVolume::fieldFunctions::DensityMassFractions::DensityMassFractions(std::shared_ptr<ablate::finiteVolume::fieldFunctions::CompressibleFlowState> flowStateIn,
                                                                                 std::shared_ptr<ablate::domain::Region> region)
    : ablate::mathFunctions::FieldFunction("densityYi", flowStateIn->GetFieldFunction("densityYi"), {}, region) {}

#include "registrar.hpp"
REGISTER(ablate::mathFunctions::FieldFunction, ablate::finiteVolume::fieldFunctions::DensityMassFractions, "initializes the densityYi conserved field variables based upon a CompressibleFlowState",
         ARG(ablate::finiteVolume::fieldFunctions::CompressibleFlowState, "state", "The CompressibleFlowState used to initialize"),
         OPT(ablate::domain::Region, "region", "A subset of the domain to apply the field function"));