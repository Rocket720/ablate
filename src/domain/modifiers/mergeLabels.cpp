#include "mergeLabels.hpp"
#include "utilities/petscError.hpp"

ablate::domain::modifiers::MergeLabels::MergeLabels(std::shared_ptr<domain::Region> mergedRegion, std::vector<std::shared_ptr<domain::Region>> regions)
    : mergedRegion(mergedRegion), regions(regions) {}

void ablate::domain::modifiers::MergeLabels::Modify(DM& dm) {
    // Create a new label for the merged region
    DMCreateLabel(dm, mergedRegion->GetName().c_str()) >> checkError;

    // Get the label for each region
    std::vector<IS> regionISs(regions.size(), nullptr);

    // Get the data
    for (std::size_t r = 0; r < regions.size(); r++) {
        auto& regionIS = regionISs[r];
        DMGetStratumIS(dm, regions[r]->GetName().c_str(), regions[r]->GetValue(), &regionIS) >> checkError;
    }
    // Create Concatenate IS
    IS mergedIS;
    ISConcatenate(PETSC_COMM_SELF, regionISs.size(), &regionISs[0], &mergedIS) >> checkError;
    ISSortRemoveDups(mergedIS) >> checkError;

    // cleanup
    for (auto& is : regionISs) {
        ISDestroy(&is) >> checkError;
    }

    DMLabel mergedLabel;
    DMGetLabel(dm, mergedRegion->GetName().c_str(), &mergedLabel) >> checkError;
    DMLabelSetStratumIS(mergedLabel, mergedRegion->GetValue(), mergedIS) >> checkError;

    // cleanup
    ISDestroy(&mergedIS) >> checkError;
    DMPlexLabelComplete(dm, mergedLabel) >> checkError;
}

#include "registrar.hpp"
REGISTER(ablate::domain::modifiers::Modifier, ablate::domain::modifiers::MergeLabels, "Creates a new label for all faces on the outside of the boundary",
         ARG(ablate::domain::Region, "mergedRegion", "the merged region to create"), ARG(std::vector<ablate::domain::Region>, "regions", "the regions to include in the new merged region"));
