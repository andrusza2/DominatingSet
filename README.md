# Minimum Dominating Set - Approximation Algorithms

Student Project,  Warsaw University of Technology 
GIS, 2017Z

## Built With

* [Boost Graph Library](http://www.boost.org/doc/libs/1_66_0/libs/graph/doc/index.html)

## Test Results

### Real Networks' Characteristics

| Network      | &#124;N&#124;   | &#124;E&#124;|
|--------------|--------|---------|
| ego-Facebook | 4,039  | 88,234  |
| ca-AstroPh   | 18,772 | 198,11  |
| ca-CondMat   | 23,133 | 93,497  |
| ca-GrQc      | 5,242  | 14,496  |
| ca-HepPh     | 12,008 | 118,521 |
| ca-HepTh     | 9,877  | 25,998  |


### Dominating Set Size

| Network      | RegularGreedy | VRegularGreedy | RegularGreedy+ | VRegularGreedy+ | FastGreedy |
|--------------|---------------|----------------|----------------|-----------------|------------|
| ego-Facebook | 10            | 10             | 587            | 10              | 10         |
| ca-AstroPh   | 2511          | 2511           | 4124           | 4124            | 3360       |
| ca-CondMat   | 3779          | 3779           | 5537           | 5537            | 4413       |
| ca-GrQc      | 1221          | 1221           | 1556           | 1556            | 1323       |
| ca-HepPh     | 2071          | 2071           | 3162           | 3162            | 2533       |
| ca-HepTh     | 2359          | 2359           | 3174           | 3174            | 2616       |

### Running Time (ms)

| Network      | RegularGreedy (ms) | VRegularGreedy (ms) | RegularGreedy+ (ms) | VRegularGreedy+ (ms) | FastGreedy (ms) |
|--------------|--------------------|---------------------|---------------------|----------------------|-----------------|
| ego-Facebook | 8                  | 4                   | 28                  | 3                    | 4               |
| ca-AstroPh   | 84273              | 84132               | 9057                | 10666                | 430             |
| ca-CondMat   | 63449              | 64839               | 14829               | 15114                | 270             |
| ca-GrQc      | 1794               | 1932                | 372                 | 362                  | 26              |
| ca-HepPh     | 32394              | 34133               | 2813                | 2790                 | 224             |
| ca-HepTh     | 10673              | 9936                | 1829                | 1858                 | 63              |

## Citation

    @article{article,
        author = {Campan, Alina and Truta, T.M. and Beckerich, M},
        year = {2015},
        month = {01},
        pages = {55-62},
        title = {Fast dominating set algorithms for social networks},
        booktitle = {CEUR Workshop Proceedings}
    }

    @inproceedings{Eubank:2004:SAA:982792.982902,
         author = {Eubank, Stephen and Kumar, V. S. Anil and Marathe, Madhav V. and Srinivasan, Aravind and Wang, Nan},
         title = {Structural and Algorithmic Aspects of Massive Social Networks},
         booktitle = {Proceedings of the Fifteenth Annual ACM-SIAM Symposium on Discrete Algorithms},
         year = {2004},
         pages = {718--727},
    } 
