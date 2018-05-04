# CERN-ROOT-Canvas-Factory
Canvas Factory for CERN ROOT

Example usage:

```
////////////////////////////////////////////////////////////////////////////////
// EXAMPLE CODE
////////////////////////////////////////////////////////////////////////////////

#include "CanvasFactory.hpp"

int main()
{
 
    Int_t num_bins{40};
    CanvasFactorySettings s("x_axis", "y_axis", 2.0, 0.0, false);
    s.SetCanvasSize(800, 600);
    s.SetAxisLabelFont(4); // default 4, 5 or something else?
    // maybe 42?
    s.SetAxisLabelFontSize(0.03);
    s.SetDrawOption("E");
    CanvasFactory f(s);
    TH1D *h_el_energy_original = new TH1D("h_el_energy_original", "", num_bins, 0.0, 4.0);
    TH1D *h_el_energy_reweight = new TH1D("h_el_energy_reweight", "", num_bins, 0.0, 4.0);
    h_el_energy_original->Fill(2.0);
    h_el_energy_original->Fill(3.0);
    h_el_energy_original->Fill(3.0);
    f.Canvas("el_energy", "el_energy_nolog_dir", h_el_energy_original, h_el_energy_reweight);

    return 0;
}
```
