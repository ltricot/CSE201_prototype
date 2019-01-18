#include <info_user.h>

info_user::info_user()
{
    // Create all the checkboxes
    QCheckBox *galax = new QCheckBox("Astrophysics of Galaxies");
    checkboxes[0]=galax;
    QCheckBox *cosmo = new QCheckBox("Cosmology and Nongalactic Astrophysics");
    checkboxes[1] = cosmo;
    QCheckBox *earth = new QCheckBox("Earth and Planetary Astrophysics");
    checkboxes[2] = earth;
    QCheckBox *heap = new QCheckBox("High Energy Astrophysical Phenomena");
    checkboxes[3] = heap;
    QCheckBox *instru = new QCheckBox("Instrumentation and Methods for Astrophysics");
    checkboxes[4] = instru;
    QCheckBox *solar = new QCheckBox("Solar and Stellar Astrophysics");
    checkboxes[5] = solar;
    QCheckBox *disorder = new QCheckBox("Disordered Systems and Neural Networks");
    checkboxes[6] = disorder;
    QCheckBox *materials = new QCheckBox("Materials Science");
    checkboxes[7] = materials;
    QCheckBox *meso = new QCheckBox("Mesoscale and Nanoscale Physics");
    checkboxes[8] = meso;
    QCheckBox *o_condens = new QCheckBox("Other Condensed Matter");
    checkboxes[9] = o_condens;
    QCheckBox *quant_gases = new QCheckBox("Quantum Gases");
    checkboxes[10] = quant_gases;
    QCheckBox *soft = new QCheckBox("Soft Condensed Matter");
    checkboxes[11] = soft;
    QCheckBox *stat_mech = new QCheckBox("Statistical Mechanics");
    checkboxes[12] = stat_mech;
    QCheckBox *corr_elect = new QCheckBox("Strongly Correlated Electrons");
    checkboxes[13] = corr_elect;
    QCheckBox *supercond = new QCheckBox("Superconductivity");
    checkboxes[14] = supercond;
    QCheckBox *adapt = new QCheckBox("Adaptation and Self-Organizing Systems");
    checkboxes[15] = adapt;
    QCheckBox *cell_auto = new QCheckBox("Cellular Automata and Lattice Gases");
    checkboxes[16] = cell_auto;
    QCheckBox *chaos = new QCheckBox("Chaotic Dynamics");
    checkboxes[17] = chaos;
    QCheckBox *solvable = new QCheckBox("Exactly Solvable and Integrable Systems");
    checkboxes[18] = solvable;
    QCheckBox *pattern_form = new QCheckBox("Pattern Formation and Solitons");
    checkboxes[19] = pattern_form;
    QCheckBox *acce = new QCheckBox("Accelerator Physics");
    checkboxes[20] = acce;
    QCheckBox *apply = new QCheckBox("Applied Physics");
    checkboxes[21] = apply;
    QCheckBox *atmo = new QCheckBox("Atmospheric and Oceanic Physics");
    checkboxes[22] = atmo;
    QCheckBox *atomic = new QCheckBox("Atomic Physics");
    checkboxes[23] = atomic;
    QCheckBox *clusters = new QCheckBox("Atomic and Molecular Clusters");
    checkboxes[24] = clusters;
    QCheckBox *bio_phy = new QCheckBox("Biological Physics");
    checkboxes[25] = bio_phy;
    QCheckBox *chem_phy = new QCheckBox("Chemical Physics");
    checkboxes[26] = chem_phy;
    QCheckBox *class_phy = new QCheckBox("Classical Physics");
    checkboxes[27] = class_phy;
    QCheckBox *comp_phy = new QCheckBox("Computational Physics");
    checkboxes[28] = comp_phy;
    QCheckBox *data_ana = new QCheckBox("Data Analysis, Statistics and Probability");
    checkboxes[29] = data_ana;
    QCheckBox *fluid = new QCheckBox("Fluid Dynamics");
    checkboxes[30] = fluid;
    QCheckBox *gen_phy = new QCheckBox("General Physics");
    checkboxes[31] = gen_phy;
    QCheckBox *geophy = new QCheckBox("Geophysics");
    checkboxes[32] = geophy;
    QCheckBox *hist_phy = new QCheckBox("History and Philosophy of Physics");
    checkboxes[33] = hist_phy;
    QCheckBox *instru_detect = new QCheckBox("Instrumentation and Detectors");
    checkboxes[34] = instru_detect;
    QCheckBox *medic = new QCheckBox("Medical Physics");
    checkboxes[35] = medic;
    QCheckBox *optics = new QCheckBox("Optics");
    checkboxes[36] = optics;
    QCheckBox *edu = new QCheckBox("Physics Education");
    checkboxes[37] = edu;
    QCheckBox *phy_socie = new QCheckBox("Physics and Society");
    checkboxes[38] = phy_socie;
    QCheckBox *plasma = new QCheckBox("Plasma Physics");
    checkboxes[39] = plasma;
    QCheckBox *pop_phy = new QCheckBox("Popular Physics");
    checkboxes[40] = pop_phy;
    QCheckBox *space_phy = new QCheckBox("Space Physics");
    checkboxes[41] = space_phy;
    QCheckBox *gen_rela = new QCheckBox("General Relativity and Quantum Cosmology");
    checkboxes[42] = gen_rela;
    QCheckBox *hep_exp = new QCheckBox("High Energy Physics - Experiment");
    checkboxes[43] = hep_exp;
    QCheckBox *hep_lat = new QCheckBox("High Energy Physics - Lattice");
    checkboxes[44] = hep_lat;
    QCheckBox *hep_pheno = new QCheckBox("High Energy Physics - Phenomenology");
    checkboxes[45] = hep_pheno;
    QCheckBox *hep_theo = new QCheckBox("High Energy Physics - Theory");
    checkboxes[46] = hep_theo;
    QCheckBox *phy_math = new QCheckBox("Mathematical Physics");
    checkboxes[47] = phy_math;
    QCheckBox *nucl_exp = new QCheckBox("Nuclear Experiment");
    checkboxes[48] = nucl_exp;
    QCheckBox *nucl_theo = new QCheckBox("Nuclear Theory");
    checkboxes[49] = nucl_theo;
    QCheckBox *quant_phy = new QCheckBox("Quantum Physics");
    checkboxes[50] = quant_phy;
    QCheckBox *alge_geo = new QCheckBox("Algebraic Geometry");
    checkboxes[51] = alge_geo;
    QCheckBox *alge_topo = new QCheckBox("Algebraic Topology");
    checkboxes[52] = alge_topo;
    QCheckBox *pde = new QCheckBox("Analysis of PDEs");
    checkboxes[53] = pde;
    QCheckBox *categ_theo = new QCheckBox("Category Theory");
    checkboxes[54] = categ_theo;
    QCheckBox *ode = new QCheckBox("Classical Analysis and ODEs");
    checkboxes[55] = ode;
    QCheckBox *combi = new QCheckBox("Combinatorics");
    checkboxes[56] = combi;
    QCheckBox *commut = new QCheckBox("Commutative Algebra");
    checkboxes[57] = commut;
    QCheckBox *complex_var = new QCheckBox("Complex Variables");
    checkboxes[58] = complex_var;
    QCheckBox *diff_geo = new QCheckBox("Differential Geometry");
    checkboxes[59] = diff_geo;
    QCheckBox *dyn_syst = new QCheckBox("Dynamical Systems");
    checkboxes[60] = dyn_syst;
    QCheckBox *func_anal = new QCheckBox("Functional Analysis");
    checkboxes[61] = func_anal;
    QCheckBox *gen_math = new QCheckBox("General Mathematics");
    checkboxes[62] = gen_math;
    QCheckBox *gen_topo = new QCheckBox("General Topology");
    checkboxes[63] = gen_topo;
    QCheckBox *geo_topo = new QCheckBox("Geometric Topology");
    checkboxes[64] = geo_topo;
    QCheckBox *group_theo = new QCheckBox("Group Theory");
    checkboxes[65] = group_theo;
    QCheckBox *hist = new QCheckBox("History and Overview");
    checkboxes[66] = hist;
    QCheckBox *info_theo_math = new QCheckBox("Information Theory");
    checkboxes[67] = info_theo_math;
    QCheckBox *k_theo = new QCheckBox("K-Theory and Homology");
    checkboxes[68] = k_theo;
    QCheckBox *logic_math = new QCheckBox("Logic");
    checkboxes[69] = logic_math;
    QCheckBox *math_phy = new QCheckBox("Mathematical Physics");
    checkboxes[70] = math_phy;
    QCheckBox *metric_geo = new QCheckBox("Metric Geometry");
    checkboxes[71] = metric_geo;
    QCheckBox *num_theo = new QCheckBox("Number Theory");
    checkboxes[72] = num_theo;
    QCheckBox *num_ana = new QCheckBox("Numerical Analysis");
    checkboxes[73] = num_ana;
    QCheckBox *op_alg = new QCheckBox("Operator Algebras");
    checkboxes[74] = op_alg;
    QCheckBox *opti = new QCheckBox("Optimization and Control");
    checkboxes[75] = opti;
    QCheckBox *proba = new QCheckBox("Probability");
    checkboxes[76] = proba;
    QCheckBox *quantum_alg = new QCheckBox("Quantum Algebra");
    checkboxes[77] = quantum_alg;
    QCheckBox *repr_theo = new QCheckBox("Representation Theory");
    checkboxes[78] = repr_theo;
    QCheckBox *ring = new QCheckBox("Rings and Algebras");
    checkboxes[79] = ring;
    QCheckBox *spec = new QCheckBox("Spectral Theory");
    checkboxes[80] = spec;
    QCheckBox *stat_theo_math = new QCheckBox("Statistics Theory");
    checkboxes[81] = stat_theo_math;
    QCheckBox *sympletic = new QCheckBox("Symplectic Geometry");
    checkboxes[82] = sympletic;
    QCheckBox *ai = new QCheckBox("Artificial Intelligence");
    checkboxes[83] = ai;
    QCheckBox *comp_lang = new QCheckBox("Computation and Language");
    checkboxes[84] = comp_lang;
    QCheckBox *complexity = new QCheckBox("Computational Complexity");
    checkboxes[85] = complexity;
    QCheckBox *cefs = new QCheckBox("Computational Engineering, Finance, and Science");
    checkboxes[86] = cefs;
    QCheckBox *comp_geo = new QCheckBox("Computational Geometry");
    checkboxes[87] = comp_geo;
    QCheckBox *cs_game_theo = new QCheckBox("Computer Science and Game Theory");
    checkboxes[88] = cs_game_theo;
    QCheckBox *vision_pattern = new QCheckBox("Computer Vision and Pattern Recognition");
    checkboxes[89] = vision_pattern;
    QCheckBox *comp_socie = new QCheckBox("Computers and Society");
    checkboxes[90] = comp_socie;
    QCheckBox *crypto = new QCheckBox("Cryptography and Security");
    checkboxes[91] = crypto;
    QCheckBox *data = new QCheckBox("Data Structures and Algorithms");
    checkboxes[92] = data;
    QCheckBox *databases = new QCheckBox("Databases");
    checkboxes[93] = databases;
    QCheckBox *library = new QCheckBox("Digital Libraries");
    checkboxes[94] = library;
    QCheckBox *discrete = new QCheckBox("Discrete Mathematics");
    checkboxes[95] = discrete;
    QCheckBox *dpcc = new QCheckBox("Distributed, Parallel, and Cluster Computing");
    checkboxes[96] = dpcc;
    QCheckBox *emerging = new QCheckBox("Emerging Technologies");
    checkboxes[97] = emerging;
    QCheckBox *formal_lang = new QCheckBox("Formal Languages and Automata Theory");
    checkboxes[98] = formal_lang;
    QCheckBox *gene_lit = new QCheckBox("General Literature");
    checkboxes[99] = gene_lit;
    QCheckBox *graphics = new QCheckBox("Graphics");
    checkboxes[100] = graphics;
    QCheckBox *hardware = new QCheckBox("Hardware Architecture");
    checkboxes[101] = hardware;
    QCheckBox *human_comp = new QCheckBox("Human-Computer Interaction");
    checkboxes[102] = human_comp;
    QCheckBox *info_retrie = new QCheckBox("Information Retrieval");
    checkboxes[103] = info_retrie;
    QCheckBox *info_theo_cs = new QCheckBox("Information Theory");
    checkboxes[104] = info_theo_cs;
    QCheckBox *logic_cs = new QCheckBox("Logic in Computer Science");
    checkboxes[105] = logic_cs;
    QCheckBox *mach_lear_cs = new QCheckBox("Machine Learning");
    checkboxes[106] = mach_lear_cs;
    QCheckBox *math_software_cs = new QCheckBox("Mathematical Software");
    checkboxes[107] = math_software_cs;
    QCheckBox *multiagent = new QCheckBox("Multiagent Systems");
    checkboxes[108] = multiagent;
    QCheckBox *multimedia = new QCheckBox("Multimedia");
    checkboxes[109] = multimedia;
    QCheckBox *network_int = new QCheckBox("Networking and Internet Architecture");
    checkboxes[110] = network_int;
    QCheckBox *neural_comp = new QCheckBox("Neural and Evolutionary Computing");
    checkboxes[111] = neural_comp;
    QCheckBox *num_anal = new QCheckBox("Numerical Analysis");
    checkboxes[112] = num_anal;
    QCheckBox *op_syst = new QCheckBox("Operating Systems");
    checkboxes[113] = op_syst;
    QCheckBox *o_cs = new QCheckBox("Other Computer Science");
    checkboxes[114] = o_cs;
    QCheckBox *perf = new QCheckBox("Performance");
    checkboxes[115] = perf;
    QCheckBox *programming = new QCheckBox("Programming Languages");
    checkboxes[116] = programming;
    QCheckBox *robot = new QCheckBox("Robotics");
    checkboxes[117] = robot;
    QCheckBox *social_net = new QCheckBox("Social and Information Networks");
    checkboxes[118] = social_net;
    QCheckBox *soft_engi = new QCheckBox("Software Engineering");
    checkboxes[119] = soft_engi;
    QCheckBox *sound_cs = new QCheckBox("Sound");
    checkboxes[120] = sound_cs;
    QCheckBox *symbol_cs = new QCheckBox("Symbolic Computation");
    checkboxes[121] = symbol_cs;
    QCheckBox *syst_control = new QCheckBox("Systems and Control");
    checkboxes[122] = syst_control;
    QCheckBox *biomol = new QCheckBox("Biomolecules");
    checkboxes[123] = biomol;
    QCheckBox *cell_beha = new QCheckBox("Cell behavior");
    checkboxes[124] = cell_beha;
    QCheckBox *genom = new QCheckBox("Genomics");
    checkboxes[125] = genom;
    QCheckBox *mol_net = new QCheckBox("Molecular networks");
    checkboxes[126] = mol_net;
    QCheckBox *neuron = new QCheckBox("Neurons and cognition");
    checkboxes[127] = neuron;
    QCheckBox *o_bio = new QCheckBox("Other quantitative biology");
    checkboxes[128] = o_bio;
    QCheckBox *pop_evol = new QCheckBox("Populations and evolution");
    checkboxes[129] = pop_evol;
    QCheckBox *quant_method = new QCheckBox("Quantitative methods");
    checkboxes[130] = quant_method;
    QCheckBox *subcell = new QCheckBox("Subcellular processes");
    checkboxes[131] = subcell;
    QCheckBox *tissues = new QCheckBox("Tissues and organs");
    checkboxes[132] = tissues;
    QCheckBox *comp_fin = new QCheckBox("Computational Finance");
    checkboxes[133] = comp_fin;
    QCheckBox *econ_fin = new QCheckBox("Economics");
    checkboxes[134] = econ_fin;
    QCheckBox *gen_fin = new QCheckBox("General finance");
    checkboxes[135] = gen_fin;
    QCheckBox *math_fin = new QCheckBox("Mathematical finance");
    checkboxes[136] = math_fin;
    QCheckBox *porto = new QCheckBox("Portofolio management");
    checkboxes[137] = porto;
    QCheckBox *price = new QCheckBox("Pricing of securities");
    checkboxes[138] = price;
    QCheckBox *risk = new QCheckBox("Risk management");
    checkboxes[139] = risk;
    QCheckBox *stat_fin = new QCheckBox("Statistical finance");
    checkboxes[140] = stat_fin;
    QCheckBox *trade = new QCheckBox("Trade and market microstructure");
    checkboxes[141] = trade;
    QCheckBox *applications = new QCheckBox("Applications");
    checkboxes[142] = applications;
    QCheckBox *compute = new QCheckBox("Computations");
    checkboxes[143] = compute;
    QCheckBox *mach_lear_stat = new QCheckBox("Machine Learning");
    checkboxes[144] = mach_lear_stat;
    QCheckBox *method = new QCheckBox("Methodology");
    checkboxes[145] = method;
    QCheckBox *o_stat = new QCheckBox("Other statistics");
    checkboxes[146] = o_stat;
    QCheckBox *stat_theo = new QCheckBox("Statistics theory");
    checkboxes[147] = stat_theo;
    QCheckBox *audio = new QCheckBox("Audio and speech processing");
    checkboxes[148] = audio;
    QCheckBox *image = new QCheckBox("Image and video processing");
    checkboxes[149] = image;
    QCheckBox *signal = new QCheckBox("Signal processing");
    checkboxes[150] = signal;
    QCheckBox *econometrics = new QCheckBox("Econometrics");
    checkboxes[151] = econometrics;
    QCheckBox *general_economics = new QCheckBox("General economics");
    checkboxes[152] = general_economics;
    QCheckBox *theoretical_econ = new QCheckBox("Theoretical economics");
    checkboxes[153] = theoretical_econ;
}

// Update of the storage list from the checkboxes
void info_user::update()
{
    for(int i = 0; i < 154; i ++)
    {
        if (checkboxes[i]->isChecked())
        {
            info.push_back(checkboxes[i]->text().QString::toStdString());
        }
    }
}

// Update the checkboxes from the storage list
void info_user::update_from_server(std::vector<std::string> a)
{
    for (int i = 0; i < 154; i ++)
    {
        if (std::find(a.begin(), a.end(), checkboxes[i]->text().QString::toStdString()) != a.end()) {
            checkboxes[i]->setChecked(true);
        }
        else {
            checkboxes[i]->setChecked(false);
        }
    }
}

// Checks a given checkbox
QCheckBox* info_user::give_check(int a)
{
    if (a > -1 or a < 154)
    {
        return checkboxes[a];
    }
}
