{
  'targets': [
    {
      'target_name': 'gpiobcm2835nodejs',
      'sources': [
        'src/gpiobcm2835nodejs.cc'
      ],
      "cflags" : [ "-lrt -lbcm2835" ],
      'conditions': [
                ['OS=="linux"', {
                  'cflags!': [
                    '-lrt -lbcm2835',
                  ],
                }],
              ],
      'include_dirs': [
        'src/gpio_functions',
      ],
      'libraries': [
        '-lbcm2835'
      ]
    }
  ]
}