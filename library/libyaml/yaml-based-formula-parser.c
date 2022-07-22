#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <yaml.h>

typedef struct {
    char * summary;
    char * webpage;
    char * version;
    char * license;
    char * git_url;
    char * git_sha;
    char * git_tag;
    char * src_url;
    char * src_sha;
    char * dep_pkg;
    char * bsystem;
    char * bscript;
    bool   binbstd;
    char * cdefine;
    char * ccflags;
    char * xxflags;
    char * ldflags;
    bool   use_zig;
    bool   parallel;
    char * prepare;
    char * install;
} Formula;

typedef enum {
    FORMULA_KEY_CODE_unknown,
    FORMULA_KEY_CODE_summary,
    FORMULA_KEY_CODE_webpage,
    FORMULA_KEY_CODE_version,
    FORMULA_KEY_CODE_license,
    FORMULA_KEY_CODE_git_url,
    FORMULA_KEY_CODE_git_sha,
    FORMULA_KEY_CODE_git_tag,
    FORMULA_KEY_CODE_src_url,
    FORMULA_KEY_CODE_src_sha,
    FORMULA_KEY_CODE_dep_pkg,
    FORMULA_KEY_CODE_bsystem,
    FORMULA_KEY_CODE_bscript,
    FORMULA_KEY_CODE_binbstd,
    FORMULA_KEY_CODE_cdefine,
    FORMULA_KEY_CODE_ccflags,
    FORMULA_KEY_CODE_xxflags,
    FORMULA_KEY_CODE_ldflags,
    FORMULA_KEY_CODE_use_zig,
    FORMULA_KEY_CODE_parallel,
    FORMULA_KEY_CODE_prepare,
    FORMULA_KEY_CODE_install
} FormulaKeyCode;

void formula_to_string(Formula * formula) {
    if (formula != NULL) {
        printf("summary: %s\n", formula->summary);
        printf("webpage: %s\n", formula->webpage);
        printf("version: %s\n", formula->version);
        printf("license: %s\n", formula->license);
        printf("git_url: %s\n", formula->git_url);
        printf("git_sha: %s\n", formula->git_sha);
        printf("git_tag: %s\n", formula->git_tag);
        printf("src_url: %s\n", formula->src_url);
        printf("src_sha: %s\n", formula->src_sha);
        printf("dep_pkg: %s\n", formula->dep_pkg);
        printf("bsystem: %s\n", formula->bsystem);
        printf("bscript: %s\n", formula->bscript);
        printf("binbstd: %d\n", formula->binbstd);
        printf("cdefine: %s\n", formula->cdefine);
        printf("ccflags: %s\n", formula->ccflags);
        printf("xxflags: %s\n", formula->xxflags);
        printf("ldflags: %s\n", formula->ldflags);
        printf("use-zig: %d\n", formula->use_zig);
        printf("prepare: %s\n", formula->prepare);
        printf("install: %s\n", formula->install);
        printf("parallel: %d\n", formula->parallel);
    }
}

void formula_free(Formula * formula) {
    if (formula != NULL) {
        if (formula->summary != NULL) {
            free(formula->summary);
            formula->summary = NULL;
        }

        if (formula->webpage != NULL) {
            free(formula->webpage);
            formula->webpage = NULL;
        }

        if (formula->version != NULL) {
            free(formula->version);
            formula->version = NULL;
        }

        if (formula->license != NULL) {
            free(formula->license);
            formula->license = NULL;
        }

        if (formula->git_url != NULL) {
            free(formula->git_url);
            formula->git_url = NULL;
        }

        if (formula->git_sha != NULL) {
            free(formula->git_sha);
            formula->git_sha = NULL;
        }

        if (formula->git_tag != NULL) {
            free(formula->git_tag);
            formula->git_tag = NULL;
        }

        if (formula->src_url != NULL) {
            free(formula->src_url);
            formula->src_url = NULL;
        }

        if (formula->src_sha != NULL) {
            free(formula->src_sha);
            formula->src_sha = NULL;
        }

        if (formula->dep_pkg != NULL) {
            free(formula->dep_pkg);
            formula->dep_pkg = NULL;
        }

        if (formula->bsystem != NULL) {
            free(formula->bsystem);
            formula->bsystem = NULL;
        }

        if (formula->bscript != NULL) {
            free(formula->bscript);
            formula->bscript = NULL;
        }

        if (formula->cdefine != NULL) {
            free(formula->cdefine);
            formula->cdefine = NULL;
        }

        if (formula->ccflags != NULL) {
            free(formula->ccflags);
            formula->ccflags = NULL;
        }

        if (formula->xxflags != NULL) {
            free(formula->xxflags);
            formula->xxflags = NULL;
        }

        if (formula->ldflags != NULL) {
            free(formula->ldflags);
            formula->ldflags = NULL;
        }

        if (formula->prepare != NULL) {
            free(formula->prepare);
            formula->prepare = NULL;
        }

        if (formula->install != NULL) {
            free(formula->install);
            formula->install = NULL;
        }

        free(formula);
        formula = NULL;
    }
}

static FormulaKeyCode formula_key_code_from_key_name(char * key) {
           if (strcmp(key, "summary") == 0) {
        return FORMULA_KEY_CODE_summary;
    } else if (strcmp(key, "webpage") == 0) {
        return FORMULA_KEY_CODE_webpage;
    } else if (strcmp(key, "version") == 0) {
        return FORMULA_KEY_CODE_version;
    } else if (strcmp(key, "license") == 0) {
        return FORMULA_KEY_CODE_license;
    } else if (strcmp(key, "git-url") == 0) {
        return FORMULA_KEY_CODE_git_url;
    } else if (strcmp(key, "git-sha") == 0) {
        return FORMULA_KEY_CODE_git_sha;
    } else if (strcmp(key, "git-tag") == 0) {
        return FORMULA_KEY_CODE_git_tag;
    } else if (strcmp(key, "src-url") == 0) {
        return FORMULA_KEY_CODE_src_url;
    } else if (strcmp(key, "src-sha") == 0) {
        return FORMULA_KEY_CODE_src_sha;
    } else if (strcmp(key, "dep-pkg") == 0) {
        return FORMULA_KEY_CODE_dep_pkg;
    } else if (strcmp(key, "bsystem") == 0) {
        return FORMULA_KEY_CODE_bsystem;
    } else if (strcmp(key, "bscript") == 0) {
        return FORMULA_KEY_CODE_bscript;
    } else if (strcmp(key, "binbstd") == 0) {
        return FORMULA_KEY_CODE_binbstd;
    } else if (strcmp(key, "ccflags") == 0) {
        return FORMULA_KEY_CODE_ccflags;
    } else if (strcmp(key, "xxflags") == 0) {
        return FORMULA_KEY_CODE_xxflags;
    } else if (strcmp(key, "cdefine") == 0) {
        return FORMULA_KEY_CODE_cdefine;
    } else if (strcmp(key, "ldflags") == 0) {
        return FORMULA_KEY_CODE_ldflags;
    } else if (strcmp(key, "prepare") == 0) {
        return FORMULA_KEY_CODE_prepare;
    } else if (strcmp(key, "install") == 0) {
        return FORMULA_KEY_CODE_install;
    } else if (strcmp(key, "use-zig") == 0) {
        return FORMULA_KEY_CODE_use_zig;
    } else if (strcmp(key, "parallel") == 0) {
        return FORMULA_KEY_CODE_parallel;
    } else {
        return FORMULA_KEY_CODE_unknown;
    }
}

void formula_set_value(FormulaKeyCode keyCode, char * value, Formula * formula) {
    switch (keyCode) {
        case FORMULA_KEY_CODE_binbstd:
            if (strcmp(value, "yes") == 0) {
                formula->binbstd = true;
            } else {
                formula->binbstd = false;
            }
            return;
        case FORMULA_KEY_CODE_use_zig:
            if (strcmp(value, "yes") == 0) {
                formula->use_zig = true;
            } else {
                formula->use_zig = false;
            }
            return;
        case FORMULA_KEY_CODE_parallel:
            if (strcmp(value, "yes") == 0) {
                formula->parallel = true;
            } else {
                formula->parallel = false;
            }
            return;
        default:
            value = strdup(value);
    }

    switch (keyCode) {
        case FORMULA_KEY_CODE_summary:  formula->summary = value; break;
        case FORMULA_KEY_CODE_webpage:  formula->webpage = value; break;
        case FORMULA_KEY_CODE_version:  formula->version = value; break;
        case FORMULA_KEY_CODE_license:  formula->license = value; break;
        case FORMULA_KEY_CODE_git_url:  formula->git_url = value; break;
        case FORMULA_KEY_CODE_git_sha:  formula->git_sha = value; break;
        case FORMULA_KEY_CODE_git_tag:  formula->git_tag = value; break;
        case FORMULA_KEY_CODE_src_url:  formula->src_url = value; break;
        case FORMULA_KEY_CODE_src_sha:  formula->src_sha = value; break;

        case FORMULA_KEY_CODE_dep_pkg:  formula->dep_pkg = value; break;

        case FORMULA_KEY_CODE_bsystem:  formula->bsystem = value; break;
        case FORMULA_KEY_CODE_bscript:  formula->bscript = value; break;
        case FORMULA_KEY_CODE_cdefine:  formula->cdefine = value; break;
        case FORMULA_KEY_CODE_ccflags:  formula->ccflags = value; break;
        case FORMULA_KEY_CODE_xxflags:  formula->xxflags = value; break;
        case FORMULA_KEY_CODE_ldflags:  formula->ldflags = value; break;

        case FORMULA_KEY_CODE_prepare:  formula->prepare = value; break;
        case FORMULA_KEY_CODE_install:  formula->install = value; break;

        default: break;
    }
}

Formula* formula_parse(const char * filepath) {
    if ((filepath == NULL) || (strcmp(filepath, "") == 0)) {
        fprintf(stderr, "%s\n", "filepath is not given.");
        return NULL;
    }

    FILE * file = fopen(filepath, "r");

    if (file == NULL) {
        perror(filepath);
        return NULL;
    }

    yaml_parser_t parser;
    yaml_token_t  token;

    // https://libyaml.docsforge.com/master/api/yaml_parser_initialize/
    if (yaml_parser_initialize(&parser) == 0) {
        perror("Failed to initialize yaml parser");
        return NULL;
    }

    yaml_parser_set_input_file(&parser, file);

    FormulaKeyCode formulaKeyCode = FORMULA_KEY_CODE_unknown;

    Formula * formula = NULL;
    formula = (Formula*)calloc(1, sizeof(Formula));
    formula->binbstd = false;
    formula->parallel= true;
    formula->use_zig = true;

    int lastTokenType = 0;

    bool success = true;

    do {
        // https://libyaml.docsforge.com/master/api/yaml_parser_scan/
        if (yaml_parser_scan(&parser, &token) == 0) {
            fprintf(stderr, "syntax error: %s\n", filepath);
            success = false;
            goto clean;
        }

        switch(token.type) {
            case YAML_KEY_TOKEN:
                lastTokenType = 1;
                break;
            case YAML_VALUE_TOKEN:
                lastTokenType = 2;
                break;
            case YAML_SCALAR_TOKEN:
                if (lastTokenType == 1) {
                    formulaKeyCode = formula_key_code_from_key_name((char*)token.data.scalar.value);
                } else if (lastTokenType == 2) {
                    formula_set_value(formulaKeyCode, (char*)token.data.scalar.value, formula);
                }
                break;
            default: 
                lastTokenType = 0;
                break;
        }

        if (token.type != YAML_STREAM_END_TOKEN) {
            yaml_token_delete(&token);
        }
    } while(token.type != YAML_STREAM_END_TOKEN);

clean:
    yaml_token_delete(&token);

    yaml_parser_delete(&parser);

    fclose(file);

    if (success) {
        return formula;
    } else {
        if (formula != NULL) {
            formula_free(formula);
        }
        return NULL;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <FILE>\n", argv[0]);
        return 0;
    }

    Formula * formula = formula_parse(argv[1]);

    if (formula != NULL) {
        formula_to_string(formula);
        formula_free(formula);
    }

    return 0;
}
