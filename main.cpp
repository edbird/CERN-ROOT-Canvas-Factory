#include "CanvasFactory.hpp"

int main()
{
 
    Int_t num_bins{10};
    CanvasFactorySettings s("x_axis", "y_axis", 0.0, 5.0, false);
    //s.SetCanvasSize(804, 628); // TODO: without this does not work!
    // TODO: colors not working
    //s.SetAxisTitleFont(4 * 10 + 2); // default 4, 5 or something else?
    //s.SetAxisLabelFont(42);
    //s.SetLegendEnable();
    // maybe 42?
    s.SetAxisTitleFontSize(0.035);
    s.SetAxisLabelFontSize(0.035);
    s.SetDrawOption("E");
    CanvasFactory f(s);
    TH1D *h_el_energy_original = new TH1D("h_el_energy_original", "", num_bins, 0.0, 4.0);
    TH1D *h_el_energy_reweight = new TH1D("h_el_energy_reweight", "", num_bins, 0.0, 4.0);
    h_el_energy_original->Fill(2.0);
    h_el_energy_original->Fill(3.0);
    h_el_energy_original->Fill(3.0);
    h_el_energy_reweight->Fill(1.0, 2.0);
    f.Canvas("el_energy", "el_energy_nolog_dir", h_el_energy_original, "Baseline", h_el_energy_reweight, "Reweighted");

    return 0;
}
