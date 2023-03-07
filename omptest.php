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

##
#echo "========== asum =========\n";
## 
#$a = $mo->ones([10000000],NDArray::float32);
#$start = hrtime(true);
#$sum = $la->asum($a);
#var_dump($sum);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->ones([10000000],NDArray::float64);
#$start = hrtime(true);
#$sum = $la->asum($a);
#var_dump($sum);
#echo hrtime(true)-$start;
#echo "\n";

#
echo "========== sum =========\n";
# 
$a = $mo->ones([10000000],NDArray::float32);
$start = hrtime(true);
$sum = $la->sum($a);
var_dump($sum);
echo hrtime(true)-$start;
echo "\n";
$a = $mo->ones([10000000],NDArray::float64);
$start = hrtime(true);
$sum = $la->sum($a);
var_dump($sum);
echo hrtime(true)-$start;
echo "\n";
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

##
#echo "========== imax =========\n";
##
#$a = $mo->arange(10000000,dtype:NDArray::float32);
#//$a = $mo->arange(10000,dtype:NDArray::float32);
#$start = hrtime(true);
#$idx = $la->imax($a);
#var_dump($idx);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->arange(10000000,dtype:NDArray::float64);
#//$a = $mo->arange(10000,dtype:NDArray::float64);
#$start = hrtime(true);
#$idx = $la->imax($a);
#var_dump($idx);
#echo hrtime(true)-$start;
#echo "\n";

##
## imin
##
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


##
#echo "========== increment =========\n";
##
#$a = $mo->zeros([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->increment($a,1);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([1,10000000],NDArray::float64);
#$start = hrtime(true);
#$la->increment($a,1);
#echo hrtime(true)-$start;
#echo "\n";

##
## reciprocal
##
#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->reciprocal($a);
#echo hrtime(true)-$start;
#echo "\n";

##
## greater
##
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

##
## greaterEqual
##
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

##
## less
##
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

##
## lessEqual
##
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

##
## multiply
##
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
#$a = $mo->zeros([1],NDArray::float32);
#$b = $mo->zeros([10000000,1],NDArray::float32);
#$start = hrtime(true);
#$la->add($a,$b);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([1],NDArray::float32);
#$b = $mo->zeros([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->add($a,$b,trans:true);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000000],NDArray::float32);
#$b = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->add($a,$b);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000000],NDArray::float32);
#$b = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->add($a,$b,trans:true);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10],NDArray::float32);
#$b = $mo->zeros([1000000,10],NDArray::float32);
#$start = hrtime(true);
#$la->add($a,$b);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10],NDArray::float32);
#$b = $mo->zeros([10,1000000],NDArray::float32);
#$start = hrtime(true);
#$la->add($a,$b,trans:true);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([1000000],NDArray::float32);
#$b = $mo->zeros([10,1000000],NDArray::float32);
#$start = hrtime(true);
#$la->add($a,$b);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([1000000],NDArray::float32);
#$b = $mo->zeros([1000000,10],NDArray::float32);
#$start = hrtime(true);
#$la->add($a,$b,trans:true);
#echo hrtime(true)-$start;
#echo "\n";


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
#echo "========== square =========\n";
##
#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->square($a);
#echo hrtime(true)-$start;
#echo "\n";

##
## sqrt
##
#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->sqrt($a);
#echo hrtime(true)-$start;
#echo "\n";

##
## rsqrt
##
#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->rsqrt($a);
#echo hrtime(true)-$start;
#echo "\n";

##
## pow
##
#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->pow($a,2);
#echo hrtime(true)-$start;
#echo "\n";

##
## exp
##
#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->exp($a);
#echo hrtime(true)-$start;
#echo "\n";

##
## log
##
#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->log($a);
#echo hrtime(true)-$start;
#echo "\n";

##
## tanh
##
#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->tanh($a);
#echo hrtime(true)-$start;
#echo "\n";

##
## sin
##
#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->sin($a);
#echo hrtime(true)-$start;
#echo "\n";

##
## cos
##
#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->cos($a);
#echo hrtime(true)-$start;
#echo "\n";

##
## tan
##
#$a = $mo->ones([1,10000000],NDArray::float32);
#$start = hrtime(true);
#$la->tan($a);
#echo hrtime(true)-$start;
#echo "\n";

##
## zeros
##
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

##
## equal
##
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

##
## astype
##
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

##
## fill
##
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

##
## nan2num
##
#$a = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->nan2num($a,0);
#echo hrtime(true)-$start;
#echo "\n";

##
## isnan
##
#$a = $mo->zeros([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->isnan($a);
#echo hrtime(true)-$start;
#echo "\n";

##
## maximum
##
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

##
## minimum
##
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

##
## UpdateAddOnehot
##
#$a = $mo->zeros([10000000],NDArray::int32);
#$start = hrtime(true);
#$la->onehot($a,10);
#echo hrtime(true)-$start;
#echo "\n";

##
## softmax
##
#$a = $mo->zeros([1000000,10],NDArray::float32);
#$start = hrtime(true);
#$la->softmax($a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10,1000000],NDArray::float32);
#$start = hrtime(true);
#$la->softmax($a);
#echo hrtime(true)-$start;
#echo "\n";



##
## matrixcopy(transpose,augmentedMatrix)
##
#$a = $mo->zeros([1000000,10],NDArray::float32);
#$start = hrtime(true);
#$la->transpose($a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10,1000000],NDArray::float32);
#$start = hrtime(true);
#$la->transpose($a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10,1000000],NDArray::float32);
#$b = $mo->zeros([10,1000001],NDArray::float32);
# [$m,$n] = $a->shape();
# [$mb,$ldB] = $b->shape();
#$start = hrtime(true);
#$blas->matrixcopy(false,$m,$n,1.0,$a->buffer(),0,$n,$b->buffer(),0,$ldB);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([1000000,10],NDArray::float32);
#$b = $mo->zeros([1000000,11],NDArray::float32);
# [$m,$n] = $a->shape();
# [$mb,$ldB] = $b->shape();
#$start = hrtime(true);
#$blas->matrixcopy(false,$m,$n,1.0,$a->buffer(),0,$n,$b->buffer(),0,$ldB);
#echo hrtime(true)-$start;
#echo "\n";

##
## imagecopy
##
#$a = $mo->zeros([1000000,10,3],NDArray::float32);
#$start = hrtime(true);
#$la->imagecopy($a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10,1000000,3],NDArray::float32);
#$start = hrtime(true);
#$la->imagecopy($a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([1000000,10,3],NDArray::float64);
#$start = hrtime(true);
#$la->imagecopy($a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10,1000000,3],NDArray::float64);
#$start = hrtime(true);
#$la->imagecopy($a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([1000000,10,3],NDArray::uint8);
#$start = hrtime(true);
#$la->imagecopy($a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10,1000000,3],NDArray::uint8);
#$start = hrtime(true);
#$la->imagecopy($a);
#echo hrtime(true)-$start;
#echo "\n";

#
# searchsorted
#
#$a = $mo->zeros([10000000],NDArray::float32);
#$x = $mo->ones([10],NDArray::float32);
#$start = hrtime(true);
#$la->searchsorted($a,$x);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10],NDArray::float32);
#$x = $mo->ones([10000000],NDArray::float32);
#$start = hrtime(true);
#$la->searchsorted($a,$x);
#echo hrtime(true)-$start;
#echo "\n";


##
## im2col1d
##
#$a = $mo->zeros([10,100000,3],NDArray::float32);
#$start = hrtime(true);
#$cols1 = $la->im2col1d(false,$a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000,100,3],NDArray::float32);
#$start = hrtime(true);
#$cols2 = $la->im2col1d(false,$a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10,100000,3],NDArray::float32);
#$start = hrtime(true);
#$la->im2col1d(true,$a,cols:$cols1);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000,100,3],NDArray::float32);
#$start = hrtime(true);
#$la->im2col1d(true,$a,cols:$cols2);
#echo hrtime(true)-$start;
#echo "\n";

#
# im2col2d
#
#$a = $mo->zeros([10,500,500,3],NDArray::float32);
#$start = hrtime(true);
#$cols1 = $la->im2col2d(false,$a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000,20,20,3],NDArray::float32);
#$start = hrtime(true);
#$cols2 = $la->im2col2d(false,$a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10,500,500,3],NDArray::float32);
#$start = hrtime(true);
#$la->im2col2d(true,$a,cols:$cols1);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000,20,20,3],NDArray::float32);
#$start = hrtime(true);
#$la->im2col2d(true,$a,cols:$cols2);
#echo hrtime(true)-$start;
#echo "\n";

##
## im2col3d
##
#$a = $mo->zeros([10,80,80,80,3],NDArray::float32);
#$start = hrtime(true);
#$cols1 = $la->im2col3d(false,$a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000,10,10,10,3],NDArray::float32);
#$start = hrtime(true);
#$cols2 = $la->im2col3d(false,$a);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10,80,80,80,3],NDArray::float32);
#$start = hrtime(true);
#$la->im2col3d(true,$a,cols:$cols1);
#echo hrtime(true)-$start;
#echo "\n";
#$a = $mo->zeros([10000,10,10,10,3],NDArray::float32);
#$start = hrtime(true);
#$la->im2col3d(true,$a,cols:$cols2);
#echo hrtime(true)-$start;
#echo "\n";

##
## reduceSum
##
#$a = $mo->zeros([10,20000,30],NDArray::float32);
#$start = hrtime(true);
#$sum = $la->reduceSum($a,axis:0);
#echo hrtime(true)-$start;
#echo "[".implode(',',$sum->shape())."]";
#echo "\n";
#$a = $mo->zeros([10,20000,30],NDArray::float32);
#$start = hrtime(true);
#$sum = $la->reduceSum($a,axis:1);
#echo hrtime(true)-$start;
#echo "[".implode(',',$sum->shape())."]";
#echo "\n";
#$a = $mo->zeros([10,20000,30],NDArray::float32);
#$start = hrtime(true);
#$sum = $la->reduceSum($a,axis:2);
#echo hrtime(true)-$start;
#echo "[".implode(',',$sum->shape())."]";
#echo "\n";

#
#echo "========== reduceMax =========\n";
#
#$a = $mo->zeros([10,20000,30],NDArray::float32);
#$start = hrtime(true);
#$max = $la->reduceMax($a,axis:0);
#echo hrtime(true)-$start;
#echo "[".implode(',',$max->shape())."]";
#echo "\n";
#$a = $mo->zeros([10,20000,30],NDArray::float32);
#$start = hrtime(true);
#$max = $la->reduceMax($a,axis:1);
#echo hrtime(true)-$start;
#echo "[".implode(',',$max->shape())."]";
#echo "\n";
#$a = $mo->zeros([10,20000,30],NDArray::float32);
#$start = hrtime(true);
#$max = $la->reduceMax($a,axis:2);
#echo hrtime(true)-$start;
#echo "[".implode(',',$max->shape())."]";
#echo "\n";

##
#echo "========== reduceArgMax =========\n";
## 
#$a = $mo->zeros([10,20000,30],NDArray::float32);
#$start = hrtime(true);
#$max = $la->reduceMax($a,axis:0);
#echo hrtime(true)-$start;
#echo "[".implode(',',$max->shape())."]";
#echo "\n";
#$a = $mo->zeros([10,20000,30],NDArray::float32);
#$start = hrtime(true);
#$max = $la->reduceMax($a,axis:1);
#echo hrtime(true)-$start;
#echo "[".implode(',',$max->shape())."]";
#echo "\n";
#$a = $mo->zeros([10,20000,30],NDArray::float32);
#$start = hrtime(true);
#$max = $la->reduceMax($a,axis:2);
#echo hrtime(true)-$start;
#echo "[".implode(',',$max->shape())."]";
#echo "\n";

#
#echo "========== repeat =========\n";
#
#$a = $mo->zeros([1000000,10],NDArray::float32);
#$start = hrtime(true);
#$out = $la->repeat($a,5,axis:1);
#echo hrtime(true)-$start;
#echo "[".implode(',',$out->shape())."]";
#echo "\n";
#$a = $mo->zeros([5,10],NDArray::float32);
#$start = hrtime(true);
#$out = $la->repeat($a,1000000,axis:1);
#echo hrtime(true)-$start;
#echo "[".implode(',',$out->shape())."]";
#echo "\n";
#$a = $mo->zeros([5,1000000],NDArray::float32);
#$start = hrtime(true);
#$out = $la->repeat($a,10,axis:1);
#echo hrtime(true)-$start;
#echo "[".implode(',',$out->shape())."]";
#echo "\n";
#$a = $mo->zeros([5,1000000],NDArray::float32);
#$start = hrtime(true);
#$out = $la->repeat($a,10,axis:0);
#echo hrtime(true)-$start;
#echo "[".implode(',',$out->shape())."]";
#echo "\n";
#$a = $mo->zeros([5,1000000],NDArray::float32);
#$start = hrtime(true);
#$out = $la->repeat($a,10,axis:2);
#echo hrtime(true)-$start;
#echo "[".implode(',',$out->shape())."]";
#echo "\n";
#$a = $mo->zeros([10,20],NDArray::float32);
#$start = hrtime(true);
#$out = $la->repeat($a,5);
#echo hrtime(true)-$start;
#echo "[".implode(',',$out->shape())."]";
#echo "\n";


#echo "sleep(1) ..";sleep(1);
echo "Finish!"; // Check Linux coredump by exiting without newline