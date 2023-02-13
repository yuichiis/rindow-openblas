<?php
require __DIR__.'/vendor/autoload.php';
if(!extension_loaded('rindow_openblas')) {
    echo "rindow_openblas extention is not loaded.\n";
    exit;
}
use Interop\Polite\Math\Matrix\NDArray;
use Interop\Polite\Math\Matrix\BLAS;
$mo = new Rindow\Math\Matrix\MatrixOperator();
$blas = new Rindow\OpenBlas\Math();
$la = $mo->laRawMode();

#$a = $mo->zeros([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->increment($a,1);
#echo hrtime(true)-$start;

#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->reciprocal($a);
#echo hrtime(true)-$start;

#$a = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->greater($a,1);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000000],NDArray::float32);
#$b = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->greater($a,$b);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([1000000,10],NDArray::float32);
#$b = $mo->zeros([10],NDArray::float32);
#$start = hrtime(true);
#$la->greater($a,$b);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10,1000000],NDArray::float32);
#$b = $mo->zeros([1000000],NDArray::float32);
#$start = hrtime(true);
#$la->greater($a,$b);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->greaterEqual($a,1);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000000],NDArray::float32);
#$b = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->greaterEqual($a,$b);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([1000000,10],NDArray::float32);
#$b = $mo->zeros([10],NDArray::float32);
#$start = hrtime(true);
#$la->greaterEqual($a,$b);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10,1000000],NDArray::float32);
#$b = $mo->zeros([1000000],NDArray::float32);
#$start = hrtime(true);
#$la->greaterEqual($a,$b);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->less($a,1);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000000],NDArray::float32);
#$b = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->less($a,$b);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([1000000,10],NDArray::float32);
#$b = $mo->zeros([10],NDArray::float32);
#$start = hrtime(true);
#$la->less($a,$b);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10,1000000],NDArray::float32);
#$b = $mo->zeros([1000000],NDArray::float32);
#$start = hrtime(true);
#$la->less($a,$b);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->lessEqual($a,1);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000000],NDArray::float32);
#$b = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->lessEqual($a,$b);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([1000000,10],NDArray::float32);
#$b = $mo->zeros([10],NDArray::float32);
#$start = hrtime(true);
#$la->lessEqual($a,$b);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10,1000000],NDArray::float32);
#$b = $mo->zeros([1000000],NDArray::float32);
#$start = hrtime(true);
#$la->lessEqual($a,$b);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->zeros([1],NDArray::float32);
#$b = $mo->zeros([10000000,1],NDArray::float32);
#$start = hrtime(true);
#$la->multiply($a,$b);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000000],NDArray::float32);
#$b = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->multiply($a,$b);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10],NDArray::float32);
#$b = $mo->zeros([1000000,10],NDArray::float32);
#$start = hrtime(true);
#$la->multiply($a,$b);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([1000000],NDArray::float32);
#$b = $mo->zeros([10,1000000],NDArray::float32);
#$start = hrtime(true);
#$la->multiply($a,$b);
#echo hrtime(true)-$start;
#echo "\n";


##
## add
##
$a = $mo->zeros([1],NDArray::float32);
$b = $mo->zeros([10000000,1],NDArray::float32);
$start = hrtime(true);
$la->add($a,$b);
echo hrtime(true)-$start;
echo "\n";
$a = $mo->zeros([1],NDArray::float32);
$b = $mo->zeros([1,10000000],NDArray::float32);
$start = hrtime(true);
$la->add($a,$b,trans:true);
echo hrtime(true)-$start;
echo "\n";
$a = $mo->zeros([10000000],NDArray::float32);
$b = $mo->zeros([10000000],NDArray::float32);
$start = hrtime(true);
$la->add($a,$b);
echo hrtime(true)-$start;
echo "\n";
$a = $mo->zeros([10000000],NDArray::float32);
$b = $mo->zeros([10000000],NDArray::float32);
$start = hrtime(true);
$la->add($a,$b,trans:true);
echo hrtime(true)-$start;
echo "\n";
$a = $mo->zeros([10],NDArray::float32);
$b = $mo->zeros([1000000,10],NDArray::float32);
$start = hrtime(true);
$la->add($a,$b);
echo hrtime(true)-$start;
echo "\n";
$a = $mo->zeros([10],NDArray::float32);
$b = $mo->zeros([10,1000000],NDArray::float32);
$start = hrtime(true);
$la->add($a,$b,trans:true);
echo hrtime(true)-$start;
echo "\n";
$a = $mo->zeros([1000000],NDArray::float32);
$b = $mo->zeros([10,1000000],NDArray::float32);
$start = hrtime(true);
$la->add($a,$b);
echo hrtime(true)-$start;
echo "\n";
$a = $mo->zeros([1000000],NDArray::float32);
$b = $mo->zeros([1000000,10],NDArray::float32);
$start = hrtime(true);
$la->add($a,$b,trans:true);
echo hrtime(true)-$start;
echo "\n";

##
## duplicate
##
#$a = $mo->zeros([1],NDArray::float32);
#$start = hrtime(true);
#$la->duplicate($a,100000000);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([100000000],NDArray::float32);
#$start = hrtime(true);
#$la->duplicate($a,1);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10],NDArray::float32);
#$start = hrtime(true);
#$la->duplicate($a,10000000);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->duplicate($a,10);
#echo hrtime(true)-$start;
#echo "\n";


##
## square
##
##$a = $mo->ones([1,10000000],NDArray::float32);
##$start = hrtime(true);
##$la->square($a);
##echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->sqrt($a);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->rsqrt($a);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->pow($a,2);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->exp($a);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->log($a);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->tanh($a);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->sin($a);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->cos($a);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->tan($a);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->zeros($a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([1,10000000],NDArray::float64);
#$start = hrtime(true);
#$la->zeros($a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([1,10000000],NDArray::int64);
#$start = hrtime(true);
#$la->zeros($a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$blas->zeros((int)($a->size()/2),$a->buffer(),0,2);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([1,10000000],NDArray::float64);
#$start = hrtime(true);
#$blas->zeros((int)($a->size()/2),$a->buffer(),0,2);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([1,10000000],NDArray::int32);
#$start = hrtime(true);
#$blas->zeros((int)($a->size()/2),$a->buffer(),0,2);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([1,10000000],NDArray::int64);
#$start = hrtime(true);
#$blas->zeros((int)($a->size()/2),$a->buffer(),0,2);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->zeros([1,10000000],NDArray::float32);
#$b = $mo->zeros([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->equal($a,$b);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([1,10000000],NDArray::int32);
#$b = $mo->zeros([1,10000000],NDArray::int32);
#$start = hrtime(true);
#$la->equal($a,$b);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->astype($a,NDArray::int32);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000000],NDArray::int32);
#$start = hrtime(true);
#$la->astype($a,NDArray::float32);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->zeros([10000000],NDArray::bool);
#$start = hrtime(true);
#$la->fill(true,$a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->fill(1,$a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000000],NDArray::int32);
#$start = hrtime(true);
#$la->fill(1,$a);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->nan2num($a,0);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->isnan($a);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->ones([10000000],NDArray::float32);
#$start = hrtime(true);
#$sum = $la->sum($a);
#var_dump($sum);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([10000000],NDArray::float64);
#$start = hrtime(true);
#$sum = $la->sum($a);
#var_dump($sum);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([10000000],NDArray::int8);
#$start = hrtime(true);
#$sum = $la->sum($a);
#var_dump($sum);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([10000000],NDArray::uint8);
#$start = hrtime(true);
#$sum = $la->sum($a);
#var_dump($sum);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([10000000],NDArray::int16);
#$start = hrtime(true);
#$sum = $la->sum($a);
#var_dump($sum);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([10000000],NDArray::uint16);
#$start = hrtime(true);
#$sum = $la->sum($a);
#var_dump($sum);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([10000000],NDArray::int32);
#$start = hrtime(true);
#$sum = $la->sum($a);
#var_dump($sum);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([10000000],NDArray::uint32);
#$start = hrtime(true);
#$sum = $la->sum($a);
#var_dump($sum);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([10000000],NDArray::int64);
#$start = hrtime(true);
#$sum = $la->sum($a);
#var_dump($sum);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([10000000],NDArray::uint64);
#$start = hrtime(true);
#$sum = $la->sum($a);
#var_dump($sum);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([10000000],NDArray::bool);
#$start = hrtime(true);
#$sum = $la->sum($a);
#var_dump($sum);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->arange(10000000,dtype:NDArray::float32);
#$start = hrtime(true);
#$idx = $la->imax($a);
#var_dump($idx);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->arange(10000000,dtype:NDArray::float64);
#$start = hrtime(true);
#$idx = $la->imax($a);
#var_dump($idx);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->arange(10000000,dtype:NDArray::float32);
#$start = hrtime(true);
#$idx = $la->imin($a);
#var_dump($idx);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->arange(10000000,dtype:NDArray::float64);
#$start = hrtime(true);
#$idx = $la->imin($a);
#var_dump($idx);
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->zeros([10000000],NDArray::float32);
#$b = $mo->ones([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->maximum($a,$b);
#var_dump($la->sum($a));
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->maximum($a,1);
#var_dump($la->sum($a));
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([1000000,10],NDArray::float32);
#$b = $mo->ones([10],NDArray::float32);
#$start = hrtime(true);
#$la->maximum($a,$b);
#var_dump($la->sum($a));
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10,1000000],NDArray::float32);
#$b = $mo->ones([1000000],NDArray::float32);
#$start = hrtime(true);
#$la->maximum($a,$b);
#var_dump($la->sum($a));
#echo hrtime(true)-$start;
#echo "\n";

#$a = $mo->zeros([10000000],NDArray::float32);
#$b = $mo->ones([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->minimum($a,$b);
#var_dump($la->sum($a));
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->minimum($a,1);
#var_dump($la->sum($a));
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([1000000,10],NDArray::float32);
#$b = $mo->ones([10],NDArray::float32);
#$start = hrtime(true);
#$la->minimum($a,$b);
#var_dump($la->sum($a));
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10,1000000],NDArray::float32);
#$b = $mo->ones([1000000],NDArray::float32);
#$start = hrtime(true);
#$la->minimum($a,$b);
#var_dump($la->sum($a));
#echo hrtime(true)-$start;
#echo "\n";
